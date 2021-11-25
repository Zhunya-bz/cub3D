/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <saltmer>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:59:57 by                   #+#    #+#             */
/*   Updated: 2021/11/25 16:09:54 by                  ###   ########.fr       */
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
