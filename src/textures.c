/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltmer <saltmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:59:57 by                   #+#    #+#             */
/*   Updated: 2021/11/25 21:40:27 by saltmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	ft_init_textures(t_data *data, int size)
{
	data->p_draw->texture->height = size;
	data->p_draw->texture->width = size;
	data->p_draw->texture->bpp = 4;
	data->p_draw->texture->size_line = size;
	data->p_draw->texture->endian = 0;
	data->p_draw->tex[0]->ptr = (int *)mlx_get_data_addr(data->p_draw->img_n,
			&data->p_draw->texture->bpp, &data->p_draw->texture->size_line,
			&data->p_draw->texture->endian);
	data->p_draw->tex[1]->ptr = (int *)mlx_get_data_addr(data->p_draw->img_s,
			&data->p_draw->texture->bpp, &data->p_draw->texture->size_line,
			&data->p_draw->texture->endian);
	data->p_draw->tex[2]->ptr = (int *)mlx_get_data_addr(data->p_draw->img_w,
			&data->p_draw->texture->bpp, &data->p_draw->texture->size_line,
			&data->p_draw->texture->endian);
	data->p_draw->tex[3]->ptr = (int *)mlx_get_data_addr(data->p_draw->img_e,
			&data->p_draw->texture->bpp, &data->p_draw->texture->size_line,
			&data->p_draw->texture->endian);
}

void	textures(t_data *data)
{
	int	size;
	int	i;

	i = -1;
	data->p_draw->img_n = mlx_xpm_file_to_image(data->p_draw->mlx,
			data->p_draw->path_n, &size, &size);
	data->p_draw->img_s = mlx_xpm_file_to_image(data->p_draw->mlx,
			data->p_draw->path_s, &size, &size);
	data->p_draw->img_w = mlx_xpm_file_to_image(data->p_draw->mlx,
			data->p_draw->path_w, &size, &size);
	data->p_draw->img_e = mlx_xpm_file_to_image(data->p_draw->mlx,
			data->p_draw->path_e, &size, &size);
	if (!data->p_draw->img_n || !data->p_draw->img_s || !data->p_draw->img_w
		|| !data->p_draw->img_e)
		ft_error(data);
	while (++i < TEXTURES)
	{
		data->p_draw->tex[i] = malloc(sizeof(t_ptr));
		if (!data->p_draw->tex[i])
			ft_error(data);
	}
	data->p_draw->texture = malloc(sizeof(t_tex));
	if (!data->p_draw->texture)
		ft_error(data);
	ft_init_textures(data, size);
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
	return (texdir);
}

void	set_texture(t_data *data)
{
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
}

void	ft_draw_texture(t_data *data, int x, int y)
{
	int	color;
	int	texdir;

	y = data->p_coord->draw_start - 1;
	set_texture(data);
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
