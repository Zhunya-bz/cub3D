/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erichell <erichell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:17:46 by                   #+#    #+#             */
/*   Updated: 2021/11/25 16:42:54 by erichell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	close_win(t_data *data)
{
	mlx_destroy_window(data->p_draw->mlx, data->p_draw->win);
	free_all(data);
	exit(0);
	return (0);
}

static void	arrow_press(t_data *data, double speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->p_coord->vec_x;
	data->p_coord->vec_x = data->p_coord->vec_x * \
	cos(speed) - data->p_coord->vec_y * sin(speed);
	data->p_coord->vec_y = old_dir_x * sin(speed) + data->p_coord->vec_y
		* cos(speed);
	old_plane_x = data->p_coord->plane_x;
	data->p_coord->plane_x = data->p_coord->plane_x * cos
		(speed) - data->p_coord->plane_y * sin(speed);
	data->p_coord->plane_y = old_plane_x * sin(speed)
		+ data->p_coord->plane_y * cos(speed);
	ft_draw_3d(data);
	ft_draw_map(data);
}

static void	press_wasd(t_data *data, double vectorX, double vectorY)
{
	if (data->p_info->arr[(int)(data->p_coord->y)][(int)
			(data->p_coord->x + vectorX * data->p_coord->move_speed)] != '1')
		data->p_coord->x += vectorX * data->p_coord->move_speed;
	if (data->p_info->arr[(int)(data->p_coord->y + vectorY
			* data->p_coord->move_speed)][(int)(data->p_coord->x)] != '1')
		data->p_coord->y += vectorY * data->p_coord->move_speed;
	ft_draw_3d(data);
	ft_draw_map(data);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		ft_putstr_fd("You're exit!\n", 1);
		close_win(data);
	}
	if (keycode == 13)
		press_wasd(data, data->p_coord->vec_x, data->p_coord->vec_y);
	if (keycode == 1)
		press_wasd(data, -data->p_coord->vec_x, -data->p_coord->vec_y);
	if (keycode == 123)
		arrow_press(data, -data->p_coord->rot_speed);
	if (keycode == 124)
		arrow_press(data, data->p_coord->rot_speed);
	if (keycode == 2)
		press_wasd(data, data->p_coord->plane_x, data->p_coord->plane_y);
	if (keycode == 0)
		press_wasd(data, -data->p_coord->plane_x, -data->p_coord->plane_y);
	return (0);
}
