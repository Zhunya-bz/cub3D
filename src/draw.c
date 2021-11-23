#include "../cub3D.h"

int ft_draw(t_data *data)
{
//	double posX = 8, posY = 11;  //x and y start position
//	double dirX = -1, dirY = 0; //initial direction vector
//	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
//
//	int width = 1600;
//	int height = 900;
//	double time = 0; //time of current frame
//	double oldTime = 0; //time of previous frame
	// printf("%c\n", map[11][8]);
	for(int x = 0; x < data->p_info->screen_width; x++)
	{
		double cameraX;

		cameraX = 2 * x / (double)data->p_info->screen_width - 1; //x-coordinate
		// in camera// space
		data->p_coord->ray_vecX = data->p_coord->vecX + data->p_coord->planeX *
														cameraX;
		data->p_coord->ray_vecY = data->p_coord->vecY +
								  data->p_coord->planeY *
								  cameraX;
		printf("%f\n", data->p_coord->ray_vecY );						  
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

		int lineHeight = (int) (data->p_info->screen_height /
							data->p_coord->perpWallDist);
		int drawStart = -lineHeight / 2 + data->p_info->screen_height/ 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + data->p_info->screen_height / 2;
		if (drawEnd >= data->p_info->screen_height)
			drawEnd = data->p_info->screen_height - 1;
		// printf("%d %d\n", drawStart, drawEnd);
		int color = 0x0000FF;
//		int color;
//		switch(map[mapX][mapY])
//		{
//			case 0:  color = 255;    break; //red
//			case 1:  color = 388;  break; //blue
//			default: color = 678; break; //white
//		}

		// if(side == 1) {color = color / 2;}
		// draw_line(x, drawStart, drawEnd, color);
		// printf("%d\n", drawStart);
		// printf("%d\n", drawEnd);
		int i = 0;
		while (drawStart + i < drawEnd)
		{
			my_pixel_put(data, x, drawStart + i, color);
			i++;
		}
		mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
								data->p_addres->img, 0, 0);
	}
	return (0);
}
