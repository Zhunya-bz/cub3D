/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erichell <erichell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:58:09 by erichell          #+#    #+#             */
/*   Updated: 2021/11/25 16:40:13 by erichell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_error(t_data *data)
{
	ft_putendl_fd("Error", 1);
	free_all(data);
	exit(1);
}

static void	init_direction_vector(t_data *data, double x, double y)
{
	data->p_coord->vec_x = x;
	data->p_coord->vec_y = y;
}

static void	init_direction_camera(t_data *data, double x, double y)
{
	data->p_coord->plane_x = x;
	data->p_coord->plane_y = y;
}

static void	init_colors_vectors(t_data *data)
{
	data->p_draw->f_color = create_trgb(0, data->p_draw->f_red,
			data->p_draw->f_green, data->p_draw->f_blue);
	data->p_draw->c_color = create_trgb(0, data->p_draw->c_red,
			data->p_draw->c_green, data->p_draw->c_blue);
	if (data->p_info->direction == 'N')
	{
		init_direction_vector(data, 0, -1);
		init_direction_camera(data, data->p_coord->angle, 0);
	}
	else if (data->p_info->direction == 'S')
	{
		init_direction_vector(data, 0, 1);
		init_direction_camera(data, -data->p_coord->angle, 0);
	}
	else if (data->p_info->direction == 'W')
	{
		init_direction_vector(data, -1, 0);
		init_direction_camera(data, 0, -data->p_coord->angle);
	}
	else if (data->p_info->direction == 'E')
	{
		init_direction_vector(data, 1, 0);
		init_direction_camera(data, 0, data->p_coord->angle);
	}
}

void	ft_draw_general(t_data *data)
{
	data->p_draw->mlx = mlx_init();
	data->p_draw->win = mlx_new_window(data->p_draw->mlx,
			data->p_info->screen_width, data->p_info->screen_height, "CUB3D!");
	data->p_addres->img = mlx_new_image(data->p_draw->mlx,
			data->p_info->screen_width, data->p_info->screen_height);
	data->p_addres->addr = mlx_get_data_addr(data->p_addres->img,
			&data->p_addres->bits_per_pixel, &data->p_addres->line_length,
			&data->p_addres->endian);
	textures(data);
	init_colors_vectors(data);
	data->p_coord->x += .5;
	data->p_coord->y += .5;
	ft_draw_3d(data);
	ft_draw_map(data);
	mlx_hook(data->p_draw->win, 2, 0, key_press, data);
	mlx_hook(data->p_draw->win, 17, 0, close_win, data);
	mlx_loop(data->p_draw->mlx);
}
