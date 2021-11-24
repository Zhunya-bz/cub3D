/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltmer <saltmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:27:14 by                   #+#    #+#             */
/*   Updated: 2021/11/24 13:39:15 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3D.h"

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->p_addres->addr + (y * data->p_addres->line_length + x *
			(data->p_addres->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static void ft_draw_rec(t_data *data, int start_i, int start_j, int color)
{
	int k;
	int l;

	k = start_i;
	while (k < SCALE + start_i) // по высоте-это у
	{
		l = start_j;
		while (l < SCALE + start_j) // по ширине-это х
		{
			my_pixel_put(data, l, k, color);
			l++;
		}
		k++;
	}
}

void ft_draw_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	ft_draw_rec(data, data->p_info->screen_height -
					  data->p_info->height * SCALE + i * SCALE + (int)data->p_coord->y * SCALE, (int)data->p_coord->x *
	SCALE,0xFF0000);
	while (i < data->p_info->height)
	{
		j = 0;
		while(data->p_info->arr[i][j])
		{
			if (data->p_info->arr[i][j] == '1')
				ft_draw_rec(data, data->p_info->screen_height -
				data->p_info->height * SCALE + i *
				SCALE, j * SCALE, 0x241a1a);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
}
