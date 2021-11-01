/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:27:14 by                   #+#    #+#             */
/*   Updated: 2021/11/01 16:23:04 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3D.h"
# define SCALE 20.0

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

float	ft_draw_vector(t_data *data, int color, float k)
{
	float i;

	i = 1;
	while (i <= 2)
	{
		data->p_coord->x_ray  = (float)(data->p_coord->x + SCALE/2);
		data->p_coord->y_ray = (float)(data->p_coord->y + SCALE/2);
		while ((data->arr[(int)(data->p_coord->y_ray/SCALE)][(int)
			(data->p_coord->x_ray/SCALE)] != '1'))
		{
			data->p_coord->x_ray  += cos(k + i * M_PI/3);
			data->p_coord->y_ray += sin(k + i * M_PI/3);
			my_pixel_put(data, data->p_coord->x_ray, data->p_coord->y_ray,
						 color);
		}
		i = i + 0.001; //количество лучей
	}
	return (k);
}

void ft_draw_line_up(t_data *data, int start_i, int start_j, int color)
{
	int k;
	int l;

	k = start_i;
	while (k > 0) // луч вверх
	{
		l = start_j;
		if (data->arr[(int)(k/SCALE)][(int)(l/SCALE)] == '1')
			return ;
		my_pixel_put(data, l, k, color);
		k--;
	}
}

void ft_draw_line_down(t_data *data, int start_i, int start_j, int color)
{
	int k;
	int l;

	k = start_i;
	while (k < data->height * SCALE) // луч вниз
	{
		l = start_j;
		if (data->arr[(int)(k/SCALE)][(int)(l/SCALE)] == '1')
			return ;
		my_pixel_put(data, l, k, color);
		k++;
	}
}

void ft_draw_line_left(t_data *data, int start_i, int start_j, int color)
{
	int k;
	int l;

	l = start_j;
	while (l > 0) // луч влево
	{
		k = start_i;
		if (data->arr[(int)(k/SCALE)][(int)(l/SCALE)] == '1')
			return ;
		my_pixel_put(data, l, k, color);
		l--;
	}
}

void ft_draw_line_right(t_data *data, int start_i, int start_j, int color)
{
	int k;
	int l;

	l = start_j;
	while (l < data->width * SCALE) // луч вправо
	{
		k = start_i;
		if (data->arr[(int)(k/SCALE)][(int)(l/SCALE)] == '1')
			return ;
		my_pixel_put(data, l, k, color);
		l++;
	}
}

void ft_draw_ray(t_data *data, int color)
{
	if (data->direction == 'N')
		data->k = ft_draw_vector(data, color, data->k * 2);
//		ft_draw_line_up(data, data->p_coord->y + SCALE/2, data->p_coord->x +
//													   SCALE/2, color);
	if (data->direction == 'S')
		data->k = ft_draw_vector(data, color, data->k * 0);
//		ft_draw_line_down(data, data->p_coord->y + SCALE/2, data->p_coord->x +
//		SCALE/2, color);
	if (data->direction == 'W')
		data->k = ft_draw_vector(data, color, data->k);
//		ft_draw_line_left(data, data->p_coord->y + SCALE/2, data->p_coord->x +
//		SCALE/2, color);
	if (data->direction == 'E')
		data->k = ft_draw_vector(data, color, 3 * data->k);
}

void move_player_up(t_data *data)
{
	if (data->arr[(int)((data->p_coord->y + SCALE/2 - 2)/SCALE)][(int)
		((data->p_coord->x + SCALE/2)/SCALE)] == '1')
		return ;
	data->k = ft_draw_vector(data, 0x000000, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
	data->p_coord->y -= 2;
	data->k = ft_draw_vector(data, 0x00FF00, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
}

void move_player_down(t_data *data)
{
	if (data->arr[(int)((data->p_coord->y + SCALE/2 + 2)/SCALE)][(int)
	((data->p_coord->x + SCALE/2)/SCALE)] == '1')
		return ;
	data->k = ft_draw_vector(data, 0x000000, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
	data->p_coord->y+=2;
	data->k = ft_draw_vector(data, 0x00FF00, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
}

void move_player_right(t_data *data)
{
	if (data->arr[(int)((data->p_coord->y + SCALE/2)/SCALE)][(int)
	((data->p_coord->x + SCALE/2 + 2)/SCALE)] == '1')
		return ;
	data->k = ft_draw_vector(data, 0x000000, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
	data->p_coord->x+=2;
	data->k = ft_draw_vector(data, 0x00FF00, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);

}

void move_player_left(t_data *data)
{
	if (data->arr[(int)((data->p_coord->y + SCALE/2)/SCALE)][(int)
	((data->p_coord->x + SCALE/2 - 2)/SCALE)] == '1')
		return ;
	data->k = ft_draw_vector(data, 0x000000, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
	data->p_coord->x-=2;
	data->k = ft_draw_vector(data, 0x000FF00, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
}

void ft_arrow_right(t_data *data)
{
	data->k = ft_draw_vector(data, 0x000000, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
	data->k = data->k + M_PI/50;
	data->k = ft_draw_vector(data, 0xFFFF00, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
}

void ft_arrow_left(t_data *data)
{
	ft_draw_vector(data, 0x000000, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
	data->k = data->k - M_PI/50;
	ft_draw_vector(data, 0xFFFF00, data->k);
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
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
	if (keycode == 124)
		ft_arrow_right(data);
	if (keycode == 123)
		ft_arrow_left(data);
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
	while (i < data->height)
	{
		j = 0;
		while(data->arr[i][j])
		{
			if (data->arr[i][j] == '1')
				ft_draw_rec(data, i * SCALE, j * SCALE, 0xFFFFFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
							data->p_addres->img, 0, 0);
}

int array_hook(int keycode, t_data *data)
{
	if (keycode == 124)
		ft_arrow_right(data);

	return (0);
}

void ft_draw_cub2d(t_data *data)
{
	data->p_draw->mlx = mlx_init();//инициализируем mlx
	data->p_draw->win = mlx_new_window(data->p_draw->mlx, data->screen_width,
									   data->screen_height, "CUB3D!");//создаем окно
	data->p_addres->img = mlx_new_image(data->p_draw->mlx, data->screen_width,
										data->screen_height);//создаем изображение с теми же параметрами
	data->p_addres->addr = mlx_get_data_addr(data->p_addres->img,
											 &data->p_addres->bits_per_pixel,
											 &data->p_addres->line_length,
											 &data->p_addres->endian);//получаем адресс изображения
	data->p_coord->x *= SCALE;//берем масшабируем координаты
	data->p_coord->y *= SCALE;//берем масшабируем координаты
	data->p_coord->x_ray = (float)(data->p_coord->x + SCALE/2);
	data->p_coord->y_ray = (float)(data->p_coord->y + SCALE/2);
	print_draw(data);//печать хранимого в data
	data->p_draw->F_color = create_trgb(0, data->p_draw->F_red, data->p_draw->F_green,
				data->p_draw->F_blue);//преобразуем цвет пола в HEX
	data->p_draw->C_color = create_trgb(0, data->p_draw->C_red,data->p_draw->C_green,
										data->p_draw->C_blue);//преобразуем цвет неба в HEX
	ft_draw_map(data); // рисовка самой 2д карты
	data->k = M_PI_2; // угол на который нужно повернуть лучи на начальном этапе
	ft_draw_ray(data, 0x00FF00);
	mlx_hook(data->p_draw->win, 2, 0, key_hook, data);//нажатие на клавиши wasd
//	mlx_hook(data->p_draw->win, 2, 0, array_hook, data);//нажатие на клавиши
//	// стрелочек
	mlx_hook(data->p_draw->win, 17, 0, close_win, data);// нажатие на крестик окна
//	mlx_loop_hook(data->p_draw->mlx, my_hook, data);
	mlx_loop(data->p_draw->mlx);
}
