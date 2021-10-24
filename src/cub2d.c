/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:27:14 by                   #+#    #+#             */
/*   Updated: 2021/10/24 11:26:23 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
# define SCALE 20.0

void ft_draw_rec(t_data *data, int start_i, int start_j, int color)
{
	int k;
	int l;

	k = start_i;
	while (k < SCALE + start_i)
	{
		l = start_j;
		while (l < SCALE + start_j)
		{
			mlx_pixel_put(data->p_draw->mlx, data->p_draw->win,
						  l, k, color);
			l++;
		}
		k++;
	}
}

int	close_win(t_data *data)
{
	mlx_destroy_window(data->p_draw->mlx, data->p_draw->win);
	free_all(data);
	exit(0);
	return (0);
}

void move_player_up(t_data *data)
{

//	printf("%f %d %f\n", ceil(data->p_coord->y/SCALE), data->p_coord->y,
//	   data->p_coord->y/sc);
	if (data->arr[(int)ceil(data->p_coord->y/SCALE) -
	1][(int)(data->p_coord->x/SCALE)] == '1')
		return ;
	ft_draw_rec(data, data->p_coord->y, data->p_coord->x,0x000000);
	data->p_coord->y--;
	ft_draw_rec(data, data->p_coord->y, data->p_coord->x,0xFF0000);
}

void move_player_down(t_data *data)
{
	if (data->arr[(int)(data->p_coord->y/SCALE) + 1][(int)
	(data->p_coord->x/SCALE)] =='1')
		return ;
	ft_draw_rec(data, data->p_coord->y, data->p_coord->x ,0x000000);
	data->p_coord->y++;
	ft_draw_rec(data, data->p_coord->y, data->p_coord->x,0xFF0000);
}

void move_player_right(t_data *data)
{
	if (data->arr[(int)(data->p_coord->y/SCALE)][(int)
	(data->p_coord->x/SCALE) + 1] =='1')
		return ;
	ft_draw_rec(data, data->p_coord->y, data->p_coord->x ,0x000000);
	data->p_coord->x++;
	ft_draw_rec(data, data->p_coord->y, data->p_coord->x,0xFF0000);
}

void move_player_left(t_data *data)
{
	if (data->arr[(int)(data->p_coord->y/SCALE)][(int)
	ceil(data->p_coord->x/SCALE) - 1] =='1')
		return ;
	ft_draw_rec(data, data->p_coord->y, data->p_coord->x ,0x000000);
	data->p_coord->x--;
	ft_draw_rec(data, data->p_coord->y, data->p_coord->x,0xFF0000);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		ft_putstr_fd("You're exit!\n", 1);
		close_win(data);
	}
	if (keycode == 1)
		move_player_down(data);
	if (keycode == 13)
		move_player_up(data);
	if (keycode == 2)
		move_player_right(data);
	if (keycode == 0)
		move_player_left(data);
	return (0);
}

void ft_draw_cub2d(t_data *data)
{
	int i;
	int j;

	i = 0;
	data->p_draw->mlx = mlx_init();
	data->p_draw->win = mlx_new_window(data->p_draw->mlx, 1024, 680, "CUB3D!");
	data->p_coord->x *= SCALE;
	data->p_coord->y *= SCALE;
	while (i < data->height)
	{
		j = 0;
		while(data->arr[i][j])
		{
			ft_draw_rec(data, data->p_coord->y, data->p_coord->x,
						0xFF0000);
			if (data->arr[i][j] == '1')
				ft_draw_rec(data, i * SCALE, j * SCALE, 0xFFFFFF);
			j++;
		}
		i++;
	}
	mlx_hook(data->p_draw->win, 2, 0, key_hook, data);
	mlx_hook(data->p_draw->win, 17, 0, close_win, data);
//	mlx_loop_hook(data->p_draw->mlx, my_hook, data);
	mlx_loop(data->p_draw->mlx);
}
