/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erichell <erichell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:58:09 by erichell          #+#    #+#             */
/*   Updated: 2021/11/25 14:04:47 by erichell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc newmain.c libft/libft.a -O3 -I. -lmlx -framework OpenGL -framework AppKit -lm

#include "../cub3D.h"

void ft_init_vectors(t_data *data, int x)
{
	double cameraX;
	cameraX = 2 * x / (double)data->p_info->screen_width - 1; //x-coordinate
	// in camera// space (-1, 1)
	data->p_coord->ray_vecX = data->p_coord->vecX + data->p_coord->planeX *
			cameraX;
	data->p_coord->ray_vecY = data->p_coord->vecY +
			data->p_coord->planeY * cameraX;
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
	}
	else
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

	hit = 0;
	while (hit == 0)
	{
		if (data->p_coord->sideDistX < data->p_coord->sideDistY)
		{
			data->p_coord->sideDistX += data->p_coord->deltaDistX;
			data->p_coord->mapX += data->p_coord->stepX;
			data->p_coord->side = 0;
		}
		else
		{
			data->p_coord->sideDistY  += data->p_coord->deltaDistY;
			data->p_coord->mapY += data->p_coord->stepY;
			data->p_coord->side = 1;
		}
		if (data->p_info->arr[data->p_coord->mapY][data->p_coord->mapX] == '1')
			hit = 1;
	}
	if (data->p_coord->side == 0)
			data->p_coord->perpWallDist = (data->p_coord->mapX - data->p_coord->x + (1 - data->p_coord->stepX) / 2) / data->p_coord->ray_vecX;
		else
			data->p_coord->perpWallDist = (data->p_coord->mapY - data->p_coord->y + (1 - data->p_coord->stepY) / 2) / data->p_coord->ray_vecY;
	// if (data->p_coord->side == 0)
	// 	data->p_coord->perpWallDist = (data->p_coord->sideDistX - data->p_coord->deltaDistX);
	// else
	// 	data->p_coord->perpWallDist = (data->p_coord->sideDistY - data->p_coord->deltaDistY);
	double eps = 1e-16;	
	if (data->p_coord->perpWallDist <= eps && data->p_coord->perpWallDist > -eps)
		data->p_coord->perpWallDist = 1;
}

void perpWall(t_data *data)
{
	data->p_draw->texture->line_height = (int) (data->p_info->screen_height /
						data->p_coord->perpWallDist);
	data->p_coord->drawStart = -data->p_draw->texture->line_height / 2 + data->p_info->screen_height/ 2;
	if (data->p_coord->drawStart < 0)
		data->p_coord->drawStart = 0;
	data->p_coord->drawEnd = data->p_draw->texture->line_height / 2 + data->p_info->screen_height / 2;
	if (data->p_coord->drawEnd >= data->p_info->screen_height)
		data->p_coord->drawEnd = data->p_info->screen_height - 1;
}
void ft_draw_texture(t_data *data, int x, int y)
{
	int color;
	int texdir;
	y = data->p_coord->drawStart - 1;
	if (data->p_coord->side == 0)
		data->p_draw->texture->wallx = data->p_coord->y + data->p_coord->perpWallDist * data->p_coord->ray_vecY;
	else
		data->p_draw->texture->wallx = data->p_coord->x + data->p_coord->perpWallDist * data->p_coord->ray_vecX;
		
	data->p_draw->texture->wallx -= floor(data->p_draw->texture->wallx);
	
	data->p_draw->texture->step = 1.0 * data->p_draw->texture->height / data->p_draw->texture->line_height;
	data->p_draw->texture->texx = (int)(data->p_draw->texture->wallx * (double)data->p_draw->texture->height);
	
	if (data->p_coord->side == 0 && data->p_coord->ray_vecX > 0)
		data->p_draw->texture->texx = data->p_draw->texture->height - data->p_draw->texture->texx - 1;
	if (data->p_coord->side == 1 && data->p_coord->ray_vecY < 0)
		data->p_draw->texture->texx = data->p_draw->texture->height - data->p_draw->texture->texx - 1;
		
	data->p_draw->texture->tex_pos = (data->p_coord->drawStart - data->p_info->screen_height / 2 + data->p_draw->texture->line_height / 2) * data->p_draw->texture->step;

	if (data->p_coord->side == 0)
	{
		if (data->p_coord->ray_vecX >= 0 && data->p_coord->mapX > \
		(int)data->p_coord->x)
			texdir = 0;
		if (data->p_coord->ray_vecX < 0 && data->p_coord->mapX < (int)\
		data->p_coord->x)
			texdir = 1;
	}
	if (data->p_coord->side == 1)
	{
		if (data->p_coord->ray_vecY > 0 && data->p_coord->mapY > (int)data->p_coord->y)
			texdir = 2;
		if (data->p_coord->ray_vecY < 0 && data->p_coord->mapY < (int)data->p_coord->y)
			texdir = 3;
	}	
	while(++y < data->p_coord->drawEnd)
	{
		data->p_draw->texture->texy = (int)data->p_draw->texture->tex_pos & (data->p_draw->texture->height - 1);
		data->p_draw->texture->tex_pos += data->p_draw->texture->step;
			color = (int)data->p_draw->tex[texdir]->ptr[data->p_draw->texture->height * data->p_draw->texture->texy + data->p_draw->texture->texx];
			if (data->p_coord->side == 1)
				color = color / 2;
			my_pixel_put(data, x, y, color);
	}
	
}

int ft_draw_3d(t_data *data)
{
	int x;
	int i;

	x = 0;
	while (x < data->p_info->screen_width)
	{
		ft_init_vectors(data, x);
		ft_init_dist(data);
		ft_dist_wall(data);
		perpWall(data);
		i = 0;
		int color = 0x6A5ACD;
		if (data->p_coord->side == 1)
			color = color / 2;
		while (i < data->p_coord->drawStart) // ceil
			my_pixel_put(data, x, i++, data->p_draw->C_color);
		i = 0;
		if (data->p_coord->drawStart + i < data->p_coord->drawEnd) //wall
			ft_draw_texture(data , x, data->p_coord->drawEnd);
		while (data->p_coord->drawEnd < data->p_info->screen_height) //floor
			my_pixel_put(data, x, data->p_coord->drawEnd++, data->p_draw->F_color);
		x++;
	}
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
	return (0);
}