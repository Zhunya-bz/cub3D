/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erichell <erichell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:58:09 by erichell          #+#    #+#             */
/*   Updated: 2021/11/23 17:05:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc newmain.c libft/libft.a -O3 -I. -lmlx -framework OpenGL -framework AppKit -lm

#include "../cub3D.h"

void ft_init_vectors(t_data *data, int x)
{
	double cameraX;

	cameraX = 2 * x / (double)data->p_info->screen_width - 1; //x-coordinate
	// in camera// space
	data->p_coord->ray_vecX = data->p_coord->vecX + data->p_coord->planeX *
			cameraX;
	data->p_coord->ray_vecY = data->p_coord->vecY +
			data->p_coord->planeY *
			cameraX;
	data->p_coord->mapX = (int) (data->p_coord->x);
	data->p_coord->mapY = (int) (data->p_coord->y);
	if (data->p_coord->ray_vecX == 0)
			data->p_coord->deltaDistX = 1e30;
	else
		data->p_coord->deltaDistX = fabs(1 / data->p_coord->ray_vecX);
	if (data->p_coord->ray_vecY == 0)
			data->p_coord->deltaDistY = 1e30;
	else
		data->p_coord->deltaDistY = fabs(1 / data->p_coord->ray_vecY);
}

void ft_init_dist(t_data *data)
{
	if (data->p_coord->ray_vecX < 0)
	{
		data->p_coord->stepX = -1;
		data->p_coord->sideDistX = (data->p_coord->x - data->p_coord->mapX) *
								   data->p_coord->deltaDistX;
	} else
	{
		data->p_coord->stepX = 1;
		data->p_coord->sideDistX = (data->p_coord->mapX + 1.0 - data->p_coord->x) * data->p_coord->deltaDistX;
	}
	if (data->p_coord->ray_vecY < 0)
	{
		data->p_coord->stepY = -1;
		data->p_coord->sideDistY = (data->p_coord->y -
									data->p_coord->mapY) * data->p_coord->deltaDistY;
	}
	else
	{
		data->p_coord->stepY = 1;
		data->p_coord->sideDistY = (data->p_coord->mapY + 1.0 -
									data->p_coord->y) * data->p_coord->deltaDistY;
	}
}

void ft_dist_wall(t_data *data)
{
	int hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (data->p_coord->sideDistX < data->p_coord->sideDistY)
		{
			data->p_coord->sideDistX += data->p_coord->deltaDistX;
			data->p_coord->mapX += data->p_coord->stepX;
			side = 0;
		}
		else
		{
			data->p_coord->sideDistY  += data->p_coord->deltaDistY;
			data->p_coord->mapY += data->p_coord->stepY;
			side = 1;
		}
		if (data->p_info->arr[data->p_coord->mapY][data->p_coord->mapX] == '1')
			hit = 1;
	}
	if (side == 0)
		data->p_coord->perpWallDist = (data->p_coord->sideDistX - data->p_coord->deltaDistX);
	else
		data->p_coord->perpWallDist = (data->p_coord->sideDistY - data->p_coord->deltaDistY);
}

int ft_draw_3d(t_data *data)
{
	int lineHeight;
	int	drawStart;
	int drawEnd;
	int x;
	int i;

	x = 0;
	i = 0;
	while (x < data->p_info->screen_width)
	{
		ft_init_vectors(data, x);
//		printf("%f %f\n", data->p_coord->deltaDistX, data->p_coord->deltaDistY);
		ft_init_dist(data);
		ft_dist_wall(data);
//		printf("%f \n", data->p_coord->perpWallDist);
//		exit(1);

		lineHeight = (int) (data->p_info->screen_height /
				data->p_coord->perpWallDist);
		drawStart = -lineHeight / 2 + data->p_info->screen_height/ 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + data->p_info->screen_height / 2;
		if (drawEnd >= data->p_info->screen_height)
			drawEnd = data->p_info->screen_height - 1;
		printf("%d %d\n", drawStart, drawEnd);
		int color = 0x0000FF;
//		switch (map[mapX][mapY])
//		{
//			case 0:
//				color = 255;
//				break; //red
//			case 1:
//				color = 388;
//				break; //blue
//			default:
//				color = 678;
//				break; //white
//		}
//		printf("%d\n", drawEnd);
		// if(side == 1) {color = color / 2;}
//		// draw_line(x, drawStart, drawEnd, color);
//	   printf("ds=%d\n", drawStart);
//       printf("de=%d\n", drawEnd);
//      int i = 0;
		i = 0;
		while (drawStart + i < drawEnd)
		{
			my_pixel_put(data, x, drawStart + i++, color);
		//        i++;
		}
		x++;
	}

	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
//	exit(1);
	return (0);
}