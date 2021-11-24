/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltmer <saltmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:27:14 by                   #+#    #+#             */
/*   Updated: 2021/11/24 12:31:57 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3D.h"
# define SCALE 16.0

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->p_addres->addr + (y * data->p_addres->line_length + x *
			(data->p_addres->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void ft_draw_rec(t_data *data, int start_i, int start_j, int color)
{
	int k;
	int l;

	k = start_i;
	while (k < SCALE + start_i) // по высоте-это у
	{
		l = start_j;
		while (l < SCALE + start_j) // по ширине-это х
		{
//			mlx_pixel_put(data->p_draw->mlx, data->p_draw->win, l, k, color);
			my_pixel_put(data, l, k, color);
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

int	key_hook(int keycode, t_data *data)
{
//	mlx_clear_window(data->p_draw->mlx, data->p_draw->win);
	if (keycode == 53)
	{
		ft_putstr_fd("You're exit!\n", 1);
		close_win(data);
	}
//	if (keycode == 1)
//		move_player_down(data);
//	if (keycode == 13)
//		move_player_up(data);
//	if (keycode == 2)
//		move_player_right(data);
//	if (keycode == 0)
//		move_player_left(data);
//	if (keycode == 124)
//		ft_arrow_right(data);
//	if (keycode == 123)
//		ft_arrow_left(data);
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void ft_draw_map(t_data *data)
{
	int i;
	int j;

	i = 0;
//	ft_draw_rec(data, data->p_coord->y, data->p_coord->x,0xFF0000);
	while (i < data->p_info->height)
	{
		j = 0;
		while(data->p_info->arr[i][j])
		{
			if (data->p_info->arr[i][j] == '1')
				ft_draw_rec(data, i * SCALE, j * SCALE, 0xFFFFFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
}

void textures(t_data *data)
{
	int size;

	data->p_draw->img_N = mlx_xpm_file_to_image(data->p_draw->mlx, data->p_draw->path_N, &size, &size);
	data->p_draw->img_S = mlx_xpm_file_to_image(data->p_draw->mlx, data->p_draw->path_S, &size, &size);
	data->p_draw->img_W = mlx_xpm_file_to_image(data->p_draw->mlx, data->p_draw->path_W, &size, &size);
	data->p_draw->img_E = mlx_xpm_file_to_image(data->p_draw->mlx, data->p_draw->path_E, &size, &size);
	if (!data->p_draw->img_N || !data->p_draw->img_S || !data->p_draw->img_W || !data->p_draw->img_E)
	{
		printf("Error\n");
		free_all(data);
		exit(1);
	}
}

void init_colors_vectors(t_data *data)
{
	data->p_draw->F_color = create_trgb(0, data->p_draw->F_red,
										data->p_draw->F_green,data->p_draw->F_blue);//преобразуем цвет пола в HEX
	data->p_draw->C_color = create_trgb(0, data->p_draw->C_red,
										data->p_draw->C_green,data->p_draw->C_blue);//преобразуем цвет неба в HEX
	if (data->p_info->direction == 'N')
	{
		data->p_coord->vecY = -1;
		data->p_coord->planeX = 0.66;
		data->p_coord->planeY = 0;
	}
	else if (data->p_info->direction == 'S')
	{
		data->p_coord->vecY = 1;
		data->p_coord->planeX = 0.66;
		data->p_coord->planeY = 0;
	}
	else if (data->p_info->direction == 'W')
		data->p_coord->vecX = 1;
	else if (data->p_info->direction == 'E')
		data->p_coord->vecX = -1;
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
	}
	//move backwards if no wall behind you
	if (keycode == 1) // S
	{
//		printf("%f %f\n", data->p_coord->x, data->p_coord->y);
		if (data->p_info->arr[(int)(data->p_coord->y)][(int)
				(data->p_coord->x - data->p_coord->vecX *
				data->p_coord->moveSpeed)] != '1')
			data->p_coord->x -= data->p_coord->vecX * data->p_coord->moveSpeed;
		if (data->p_info->arr[(int)(data->p_coord->y - data->p_coord->vecY *
													   data->p_coord->moveSpeed)][(int)(data->p_coord->x)] != '1')
			data->p_coord->y -= data->p_coord->vecY * data->p_coord->moveSpeed;
		ft_draw_3d(data);
	}
	//rotate to the right
	if(keycode == 124) // D
	{
		//both camera direction and camera plane must be rotated
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
	}
	//rotate to the left
	if(keycode == 123) // A
	{
		//both camera direction and camera plane must be rotated
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
	}
	return (0);
}

void ft_draw_cub2d(t_data *data)
{
	data->p_draw->mlx = mlx_init();
	data->p_draw->win = mlx_new_window(data->p_draw->mlx,
									   data->p_info->screen_width,
									   data->p_info->screen_height,
									   "CUB3D!");//создаем окно
	data->p_addres->img = mlx_new_image(data->p_draw->mlx,
										data->p_info->screen_width,
										data->p_info->screen_height);//создаем изображение с теми же параметрами
	data->p_addres->addr = mlx_get_data_addr(data->p_addres->img,
											 &data->p_addres->bits_per_pixel,
											 &data->p_addres->line_length,
											 &data->p_addres->endian);//получаем адресс изображения
	textures(data);
	init_colors_vectors(data);

	ft_draw_3d(data); //рисовка в 3D
//	ft_draw(data);
	ft_draw_map(data); // рисовка самой 2д карты

//	data->p_info->k = M_PI_2; // угол на который нужно повернуть лучи на начальном этапе
//	ft_draw_ray(data, 0x00FF00);

	mlx_hook(data->p_draw->win, 2, 0, key_press, data);
	mlx_hook(data->p_draw->win, 17, 0, close_win, data);// нажатие на крестик окна
	mlx_loop(data->p_draw->mlx);
//	exit(1);
}
