/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltmer <saltmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:58:09 by erichell          #+#    #+#             */
/*   Updated: 2021/11/26 11:06:10 by saltmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_init_vectors(t_data *data, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)data->p_info->screen_width - 1;
	data->p_coord->ray_vec_x = data->p_coord->vec_x + data->p_coord->plane_x * \
			camera_x;
	data->p_coord->ray_vec_y = data->p_coord->vec_y + \
			data->p_coord->plane_y * camera_x;
	data->p_coord->map_x = (int)(data->p_coord->x);
	data->p_coord->map_y = (int)(data->p_coord->y);
	if (data->p_coord->ray_vec_x == 0)
		data->p_coord->delta_dist_x = 1e30;
	else
		data->p_coord->delta_dist_x = fabs(1 / data->p_coord->ray_vec_x);
	if (data->p_coord->ray_vec_y == 0)
		data->p_coord->delta_dist_y = 1e30;
	else
		data->p_coord->delta_dist_y = fabs(1 / data->p_coord->ray_vec_y);
}

void	ft_init_dist(t_data *data)
{
	if (data->p_coord->ray_vec_x < 0)
	{
		data->p_coord->step_x = -1;
		data->p_coord->side_dist_x = (data->p_coord->x - data->p_coord->map_x) \
		* data->p_coord->delta_dist_x;
	}
	else
	{
		data->p_coord->step_x = 1;
		data->p_coord->side_dist_x = (data->p_coord->map_x + 1.0 - \
		data->p_coord->x) * data->p_coord->delta_dist_x;
	}
	if (data->p_coord->ray_vec_y < 0)
	{
		data->p_coord->step_y = -1;
		data->p_coord->side_dist_y = (data->p_coord->y - \
	data->p_coord->map_y) * data->p_coord->delta_dist_y;
	}
	else
	{
		data->p_coord->step_y = 1;
		data->p_coord->side_dist_y = (data->p_coord->map_y + 1.0 - \
		data->p_coord->y) * data->p_coord->delta_dist_y;
	}
}

void	perp_wall_cont(t_data *data)
{
	double		eps;

	eps = 1e-16;
	if (data->p_coord->side == 0)
		data->p_coord->perp_wall_dist = (data->p_coord->map_x - \
		data->p_coord->x + (1 - data->p_coord->step_x) / 2) / \
		data->p_coord->ray_vec_x;
	else
		data->p_coord->perp_wall_dist = (data->p_coord->map_y - \
		data->p_coord->y + (1 - data->p_coord->step_y) / 2) / \
		data->p_coord->ray_vec_y;
	if (data->p_coord->perp_wall_dist <= eps && data->p_coord->perp_wall_dist \
	> -eps)
		data->p_coord->perp_wall_dist = 1;
}

void	ft_dist_wall(t_data *data)
{
	int			hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->p_coord->side_dist_x < data->p_coord->side_dist_y)
		{
			data->p_coord->side_dist_x += data->p_coord->delta_dist_x;
			data->p_coord->map_x += data->p_coord->step_x;
			data->p_coord->side = 0;
		}
		else
		{
			data->p_coord->side_dist_y += data->p_coord->delta_dist_y;
			data->p_coord->map_y += data->p_coord->step_y;
			data->p_coord->side = 1;
		}
		if (data->p_info->arr[data->p_coord->map_y][data->p_coord->map_x] \
		== '1')
			hit = 1;
	}
	perp_wall_cont(data);
}

void	perpwall(t_data *data)
{
	data->p_draw->texture->line_height = (int)(data->p_info->screen_height / \
	data->p_coord->perp_wall_dist);
	data->p_coord->draw_start = -data->p_draw->texture->line_height / 2 + \
	data->p_info->screen_height / 2;
	if (data->p_coord->draw_start < 0)
		data->p_coord->draw_start = 0;
	data->p_coord->draw_end = data->p_draw->texture->line_height / 2 + \
	data->p_info->screen_height / 2;
	if (data->p_coord->draw_end >= data->p_info->screen_height)
		data->p_coord->draw_end = data->p_info->screen_height - 1;
}
