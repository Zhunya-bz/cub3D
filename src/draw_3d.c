/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erichell <erichell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:58:09 by erichell          #+#    #+#             */
/*   Updated: 2021/11/25 16:27:23 by erichell         ###   ########.fr       */
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
		data->p_coord->side_dist_x = (data->p_coord->x - data->p_coord->map_x) * \
		data->p_coord->delta_dist_x;
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

void	ft_dist_wall(t_data *data)
{
	int			hit;
	double		eps;

	eps = 1e-16;
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
		if (data->p_info->arr[data->p_coord->map_y][data->p_coord->map_x] == '1')
			hit = 1;
	}
	if (data->p_coord->side == 0)
		data->p_coord->perp_wall_dist = (data->p_coord->map_x - data->p_coord->x \
		+ (1 - data->p_coord->step_x) / 2) / data->p_coord->ray_vec_x;
	else
		data->p_coord->perp_wall_dist = (data->p_coord->map_y - data->p_coord->y + \
	(1 - data->p_coord->step_y) / 2) / data->p_coord->ray_vec_y;
	if (data->p_coord->perp_wall_dist <= eps && data->p_coord->perp_wall_dist \
	> -eps)
		data->p_coord->perp_wall_dist = 1;
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

int	init_textures(t_data *data)
{
	int	texdir;

	if (data->p_coord->side == 0)
	{
		if (data->p_coord->ray_vec_x >= 0 && data->p_coord->map_x > \
		(int)data->p_coord->x)
			texdir = 2;
		if (data->p_coord->ray_vec_x < 0 && data->p_coord->map_x < (int) \
		data->p_coord->x)
			texdir = 3;
	}
	if (data->p_coord->side == 1)
	{
		if (data->p_coord->ray_vec_y > 0 && data->p_coord->map_y > \
		(int)data->p_coord->y)
			texdir = 1;
		if (data->p_coord->ray_vec_y < 0 && data->p_coord->map_y < \
		(int)data->p_coord->y)
			texdir = 0;
	}
	return(texdir);
}
void	ft_draw_texture(t_data *data, int x, int y)
{
	int	color;
	int	texdir;

	y = data->p_coord->draw_start - 1;
	if (data->p_coord->side == 0)
		data->p_draw->texture->wallx = data->p_coord->y + \
	data->p_coord->perp_wall_dist * data->p_coord->ray_vec_y;
	else
		data->p_draw->texture->wallx = data->p_coord->x + \
	data->p_coord->perp_wall_dist * data->p_coord->ray_vec_x;
	data->p_draw->texture->wallx -= floor(data->p_draw->texture->wallx);
	data->p_draw->texture->step = 1.0 * data->p_draw->texture->height \
	/ data->p_draw->texture->line_height;
	data->p_draw->texture->texx = (int)(data->p_draw->texture->wallx * \
	(double)data->p_draw->texture->height);
	if (data->p_coord->side == 0 && data->p_coord->ray_vec_x > 0)
		data->p_draw->texture->texx = data->p_draw->texture->height \
	- data->p_draw->texture->texx - 1;
	if (data->p_coord->side == 1 && data->p_coord->ray_vec_y < 0)
		data->p_draw->texture->texx = data->p_draw->texture->height \
	- data->p_draw->texture->texx - 1;
	data->p_draw->texture->tex_pos = (data->p_coord->draw_start - \
	data->p_info->screen_height / 2 + data->p_draw->texture->line_height \
	/ 2) * data->p_draw->texture->step;
	texdir = init_textures(data);
	
	while (++y < data->p_coord->draw_end)
	{
		data->p_draw->texture->texy = (int)data->p_draw->texture->tex_pos \
		& (data->p_draw->texture->height - 1);
		data->p_draw->texture->tex_pos += data->p_draw->texture->step;
		color = (int)data->p_draw->tex[texdir]->ptr[data->p_draw-> \
		texture->height * data->p_draw->texture->texy + \
		data->p_draw->texture->texx];
		my_pixel_put(data, x, y, color);
	}
}

int	ft_draw_3d(t_data *data)
{
	int	x;
	int	i;
	int	color;

	x = 0;
	while (x < data->p_info->screen_width)
	{
		ft_init_vectors(data, x);
		ft_init_dist(data);
		ft_dist_wall(data);
		perpwall(data);
		i = 0;
		color = 0x6A5ACD;
		if (data->p_coord->side == 1)
			color = color / 2;
		while (i < data->p_coord->draw_start)
			my_pixel_put(data, x, i++, data->p_draw->c_color);
		i = 0;
		if (data->p_coord->draw_start + i < data->p_coord->draw_end)
			ft_draw_texture(data, x, data->p_coord->draw_end);
		while (data->p_coord->draw_end < data->p_info->screen_height)
			my_pixel_put(data, x, data->p_coord->draw_end++, \
		data->p_draw->f_color);
		x++;
	}
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win, \
	data->p_addres->img, 0, 0);
	return (0);
}
