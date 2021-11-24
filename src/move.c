#include "../cub3D.h"

int	close_win(t_data *data)
{
	mlx_destroy_window(data->p_draw->mlx, data->p_draw->win);
	free_all(data);
	exit(0);
	return (0);
}

static void arrow_press(t_data *data, double speed)
{
	double oldDirX;

	oldDirX = data->p_coord->vecX;
	data->p_coord->vecX = data->p_coord->vecX * cos(speed) - data->p_coord->vecY * sin
			(speed);
	data->p_coord->vecY = oldDirX * sin(speed) + data->p_coord->vecY *cos
			(speed);
	double oldPlaneX;

	oldPlaneX = data->p_coord->planeX;
	data->p_coord->planeX = data->p_coord->planeX * cos
			(speed) - data->p_coord->planeY * sin(speed);
	data->p_coord->planeY = oldPlaneX * sin(speed) +
							data->p_coord->planeY * cos(speed);
	ft_draw_3d(data);
	ft_draw_map(data); // рисовка самой 2д карты
}

static void press_WASD(t_data *data, double vectorX, double vectorY)
{
	if (data->p_info->arr[(int)(data->p_coord->y)][(int)
			(data->p_coord->x + vectorX * data->p_coord->moveSpeed)] != '1')
		data->p_coord->x += vectorX * data->p_coord->moveSpeed;
	if (data->p_info->arr[(int)(data->p_coord->y + vectorY *
												   data->p_coord->moveSpeed)][(int)(data->p_coord->x)] != '1')
		data->p_coord->y += vectorY * data->p_coord->moveSpeed;
	ft_draw_3d(data);
	ft_draw_map(data); // рисовка самой 2д карты
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		ft_putstr_fd("You're exit!\n", 1);
		close_win(data);
	}
	if (keycode == 13) // W
		press_WASD(data, data->p_coord->vecX, data->p_coord->vecY);
	if (keycode == 1) // S
		press_WASD(data, -data->p_coord->vecX, -data->p_coord->vecY);
	if (keycode == 123) // left
		arrow_press(data, -data->p_coord->rotSpeed);
	if (keycode == 124) // right
		arrow_press(data, data->p_coord->rotSpeed);
	if (keycode == 2) // D
		press_WASD(data, data->p_coord->planeX, data->p_coord->planeY);
	if (keycode == 0) // A
		press_WASD(data, -data->p_coord->planeX, -data->p_coord->planeY);
	return (0);
}
