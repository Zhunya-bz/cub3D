#include "../cub3D.h"

int	close_win(t_data *data)
{
	mlx_destroy_window(data->p_draw->mlx, data->p_draw->win);
	free_all(data);
	exit(0);
	return (0);
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		ft_putstr_fd("You're exit!\n", 1);
		close_win(data);
	}
	if (keycode == 13) // W
	{
		if (data->p_info->arr[(int)(data->p_coord->y)][(int)
				(data->p_coord->x + data->p_coord->vecX * data->p_coord->moveSpeed)]
			!= '1')
			data->p_coord->x += data->p_coord->vecX * data->p_coord->moveSpeed;
		if (data->p_info->arr[(int)(data->p_coord->y + data->p_coord->vecY *
													   data->p_coord->moveSpeed)][(int)(data->p_coord->x)] != '1')
			data->p_coord->y += data->p_coord->vecY * data->p_coord->moveSpeed;
		ft_draw_3d(data);
		ft_draw_map(data); // рисовка самой 2д карты
	}
	if (keycode == 1) // S
	{
		if (data->p_info->arr[(int)(data->p_coord->y)][(int)
				(data->p_coord->x - data->p_coord->vecX *
									data->p_coord->moveSpeed)] != '1')
			data->p_coord->x -= data->p_coord->vecX * data->p_coord->moveSpeed;
		if (data->p_info->arr[(int)(data->p_coord->y - data->p_coord->vecY *
													   data->p_coord->moveSpeed)][(int)(data->p_coord->x)] != '1')
			data->p_coord->y -= data->p_coord->vecY * data->p_coord->moveSpeed;
		ft_draw_3d(data);
		ft_draw_map(data); // рисовка самой 2д карты
	}
	if (keycode == 123) // left
	{
		double oldDirX = data->p_coord->vecX;
		data->p_coord->vecX = data->p_coord->vecX * cos
				(-data->p_coord->rotSpeed) - data->p_coord->vecY * sin
				(-data->p_coord->rotSpeed);
		data->p_coord->vecY = oldDirX * sin(-data->p_coord->rotSpeed) +
							  data->p_coord->vecY *cos(-data->p_coord->rotSpeed);
		double oldPlaneX = data->p_coord->planeX;
		data->p_coord->planeX = data->p_coord->planeX * cos
				(-data->p_coord->rotSpeed) -
								data->p_coord->planeY * sin(-data->p_coord->rotSpeed);
		data->p_coord->planeY = oldPlaneX * sin(-data->p_coord->rotSpeed) +
								data->p_coord->planeY * cos(-data->p_coord->rotSpeed);
		ft_draw_3d(data);
		ft_draw_map(data); // рисовка самой 2д карты
	}
	if (keycode == 124) // right
	{
		double oldDirX = data->p_coord->vecX;
		data->p_coord->vecX = data->p_coord->vecX * cos
				(data->p_coord->rotSpeed) - data->p_coord->vecY * sin
				(data->p_coord->rotSpeed);
		data->p_coord->vecY = oldDirX * sin(data->p_coord->rotSpeed) +
							  data->p_coord->vecY *cos(data->p_coord->rotSpeed);
		double oldPlaneX = data->p_coord->planeX;
		data->p_coord->planeX = data->p_coord->planeX * cos
				(data->p_coord->rotSpeed) -	data->p_coord->planeY * sin(data->p_coord->rotSpeed);
		data->p_coord->planeY = oldPlaneX * sin(data->p_coord->rotSpeed) +
								data->p_coord->planeY * cos(data->p_coord->rotSpeed);
		ft_draw_3d(data);
		ft_draw_map(data); // рисовка самой 2д карты
	}
	if (keycode == 2) // D
	{
		if (data->p_info->arr[(int)(data->p_coord->y)][(int)(data->p_coord->x + data->p_coord->planeX * data->p_coord->moveSpeed)]!= '1')
			data->p_coord->x += data->p_coord->planeX * data->p_coord->moveSpeed + 0.00001;
		if (data->p_info->arr[(int)(data->p_coord->y + data->p_coord->planeY * data->p_coord->moveSpeed)][(int)(data->p_coord->x)] != '1')
			data->p_coord->y += data->p_coord->planeY * data->p_coord->moveSpeed + 0.00001;
		ft_draw_3d(data);
		ft_draw_map(data); // рисовка самой 2д карты
	}
	if (keycode == 0) //A
	{
		if (data->p_info->arr[(int)(data->p_coord->y)][(int)(data->p_coord->x - data->p_coord->planeX * data->p_coord->moveSpeed)]!= '1')
			data->p_coord->x -= data->p_coord->planeX * data->p_coord->moveSpeed + 0.00001;
		if (data->p_info->arr[(int)(data->p_coord->y - data->p_coord->planeY * data->p_coord->moveSpeed)][(int)(data->p_coord->x)] != '1')
			data->p_coord->y -= data->p_coord->planeY * data->p_coord->moveSpeed + 0.00001;
		ft_draw_3d(data);
		ft_draw_map(data); // рисовка самой 2д карты
	}
	return (0);
}
