/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltmer <saltmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 12:27:14 by                   #+#    #+#             */
/*   Updated: 2021/11/23 14:33:04 by                  ###   ########.fr       */
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
//
//float ft_draw_vector2(t_data *data, int color, float k) // k - поворот на угол
//{
//	float i;
//	float ceil;
//	float floor;
//	float c;
//
//	i = 1;
//	c = 0;
//	data->p_info->pov = k + M_PI/3 + M_PI_2/3; // куда смотрит камера
//	while (i <= 2)
//	{
//		data->p_coord->x_ray = (float)(data->p_coord->x + SCALE/2);
//		data->p_coord->y_ray = (float)(data->p_coord->y + SCALE/2);
//		c = 0.1;
//		while (data->p_coord->x_ray < data->p_info->width * SCALE &&
//		data->p_coord->x_ray > SCALE && data->p_coord->y_ray > SCALE &&
//		data->p_coord->y_ray < data->p_info->height * SCALE)
//		{
//			//			printf("%f\n", c);
//			if (data->p_info->arr[(int)(data->p_coord->y_ray/SCALE)][(int)
//			(data->p_coord->x_ray/SCALE)] == '1')
//				break ;
//			data->p_coord->x_ray += c * cos(k + i * M_PI/3);// угол между лучами
//			// = 60 от пи/3 до 2пи/3
//			data->p_coord->y_ray += c * sin(k + i * M_PI/3);
//			my_pixel_put(data, data->p_coord->x_ray, data->p_coord->y_ray,
//						 color);
//			c += 0.01;
//		}
////		float dist2;
////		dist2 = sqrtf((data->p_coord->x_ray - data->p_coord->x - SCALE/2)*
////				(data->p_coord->x_ray - data->p_coord->x - SCALE/2) +
////				(data->p_coord->y_ray - data->p_coord->y - SCALE/2) *
////				(data->p_coord->y_ray - data->p_coord->y - SCALE/2));
//		float H = data->p_info->screen_height/c;
//		printf("c=%f 1/c=%f H=%f\n", c, 1/c, H);
//		ceil = data->p_info->screen_height/2 - data->p_info->screen_height*c;
//		floor = data->p_info->screen_height - ceil;
//		printf("ceil=%f floor=%f\n", ceil, floor);
//		i += 0.1;
//	}
//	return (0);
//}
//
//float	ft_draw_vector(t_data *data, int color, float k) // k - поворот на угол
//{
//	float i;
//	float ceil;
//	float floor;
////	float c;
//	int x = 0;
//	float y = 0;
//
////	if (x == 0)
////	{
////		ft_draw_vector2(data, color, k);
////		return (0);
////	}
//
//	i = 1;
////	c = 0;
//	data->p_info->pov = k + M_PI/3 + M_PI_2/3; // куда смотрит камера
////	printf("%f %f\n", data->pov, k);
//	int g = 0;
//	while (i <= 2)
//	{
//		data->p_coord->x_ray = (float)(data->p_coord->x + SCALE/2);
//		data->p_coord->y_ray = (float)(data->p_coord->y + SCALE/2);
////		while ((data->arr[(int)(data->p_coord->y_ray/SCALE)][(int)
////			(data->p_coord->x_ray/SCALE)] != '1'))
////		c = 1;
////		while (data->p_coord->x_ray < data->width * SCALE &&
////		data->p_coord->x_ray > SCALE && data->p_coord->y_ray > SCALE &&
////		data->p_coord->y_ray < data->height * SCALE)
//		while (data->p_info->arr[(int)(data->p_coord->y_ray/SCALE)][(int)
//			(data->p_coord->x_ray/SCALE)] != '1')
//		{
////			printf("%f\n", c);
////			if (data->arr[(int)(data->p_coord->y_ray/SCALE)][(int)
////			(data->p_coord->x_ray/SCALE)] == '1')
////				break ;
//			data->p_coord->x_ray += cos(k + i * M_PI/3);// угол между лучами = 60 от пи/3 до 2пи/3
//			data->p_coord->y_ray += sin(k + i * M_PI/3);
//			my_pixel_put(data, data->p_coord->x_ray, data->p_coord->y_ray,
//						 color);
////			c += 0.01;
//		}
//		float dist2;
//
//		dist2 = sqrtf((data->p_coord->x_ray - data->p_coord->x - SCALE/2)*
//				(data->p_coord->x_ray - data->p_coord->x - SCALE/2) +
//				(data->p_coord->y_ray - data->p_coord->y - SCALE/2) *
//				(data->p_coord->y_ray - data->p_coord->y - SCALE/2));
////		printf("dist2=%f\n", dist2);
////		printf("cos=%10f\n", cos(k + i * M_PI/3));
////		double eps = 0.000001;
////		if (cos(k + i * M_PI/3) < eps)
////		{
////			data->dist = data->p_coord->y - data->p_coord->y_ray - SCALE/2;
////			printf("line=%f\n", data->dist);
////		}
////		else
////			data->dist = fabs((data->p_coord->x_ray - data->p_coord->x - SCALE/2)
////					/(cos(k + i * M_PI/3)));
////		printf("c=%f dist=%f\n", c, data->dist);
////		float dist_r;
////		dist_r = dist2 * fabs(cos(k + i * M_PI/3));
////		printf("dist=%f d_r=%f\n", dist2, dist_r);
////		float H = data->screen_height/dist2;
////		printf("H=%f\n", H);
////		float dis = (float)(data->screen_height)/dist2;
////		printf("dis: %f\n", dis);
//		ceil = (float)data->p_info->screen_height/2 - (float)(data->p_info->screen_height)/dist2;
//		floor = data->p_info->screen_height - ceil;
////		printf("ceil=%f floor=%f\n", ceil, floor);
////		if (g > 15)
////			exit(0);
//		g++;
//		y = 0;
////		if (x == data->screen_width/2)
////			printf("w/2=%.16f ceil=%f floor=%f\n",
////				   dist2,ceil,floor);
////		else if (x == 200)
////			printf("%.16f ceil=%f floor=%f\n", dist2, ceil, floor);
//			while (y < round(ceil) && y >= 0)
//				my_pixel_put(data, x, y++, 0x000000);
//			while (y >= round(ceil) && y <= round(floor))
//				my_pixel_put(data, x, y++, 0xc9e9ff);
//			while (y > round(floor) && y < data->p_info->screen_height)
//				my_pixel_put(data, x, y++, 0x000000);
//		x++;
//		i += 0.00078125; //количество лучей
//	}
//	ft_draw_map(data); // рисовка самой 2д карты
//	return (k);
//}
//
//float ft_black_vector(t_data *data, int color, float k)
//{
//	float i;
//
//	i = 1;
//	data->p_coord->x_ray = (float)(data->p_coord->x + SCALE/2);
//	data->p_coord->y_ray = (float)(data->p_coord->y + SCALE/2);
////	printf("%f\n", k);
//	while (i * M_PI/3 < M_PI/50 + M_PI/3)
//	{
//		printf("%f\n", i);
//		while ((data->p_info->arr[(int)(data->p_coord->y_ray/SCALE)][(int)
//		(data->p_coord->x_ray/SCALE)] != '1'))
//		{
//			data->p_coord->x_ray += cos(k + i * M_PI/3);// угол между лучами
//			// = 60 от пи/3 до 2пи/3
//			data->p_coord->y_ray += sin(k + i * M_PI/3);
//			my_pixel_put(data, data->p_coord->x_ray, data->p_coord->y_ray,
//						 color);
//		}
//		i += 0.001;
//	}
//	return (k);
//}
//
//void ft_draw_line_up(t_data *data, int start_i, int start_j, int color)
//{
//	int k;
//	int l;
//
//	k = start_i;
//	while (k > 0) // луч вверх
//	{
//		l = start_j;
//		if (data->p_info->arr[(int)(k/SCALE)][(int)(l/SCALE)] == '1')
//			return ;
//		my_pixel_put(data, l, k, color);
//		k--;
//	}
//}
//
//void ft_draw_line_down(t_data *data, int start_i, int start_j, int color)
//{
//	int k;
//	int l;
//
//	k = start_i;
//	while (k < data->p_info->height * SCALE) // луч вниз
//	{
//		l = start_j;
//		if (data->p_info->arr[(int)(k/SCALE)][(int)(l/SCALE)] == '1')
//			return ;
//		my_pixel_put(data, l, k, color);
//		k++;
//	}
//}
//
//void ft_draw_line_left(t_data *data, int start_i, int start_j, int color)
//{
//	int k;
//	int l;
//
//	l = start_j;
//	while (l > 0) // луч влево
//	{
//		k = start_i;
//		if (data->p_info->arr[(int)(k/SCALE)][(int)(l/SCALE)] == '1')
//			return ;
//		my_pixel_put(data, l, k, color);
//		l--;
//	}
//}
//
//void ft_draw_line_right(t_data *data, int start_i, int start_j, int color)
//{
//	int k;
//	int l;
//
//	l = start_j;
//	while (l < data->p_info->width * SCALE) // луч вправо
//	{
//		k = start_i;
//		if (data->p_info->arr[(int)(k/SCALE)][(int)(l/SCALE)] == '1')
//			return ;
//		my_pixel_put(data, l, k, color);
//		l++;
//	}
//}
//
//void ft_draw_ray(t_data *data, int color)
//{
//	if (data->p_info->direction == 'N')
//		data->p_info->k = ft_draw_vector(data, color, data->p_info->k * 2);
////		ft_draw_line_up(data, data->p_coord->y + SCALE/2, data->p_coord->x +
////													   SCALE/2, color);
//	if (data->p_info->direction == 'S')
//		data->p_info->k = ft_draw_vector(data, color, data->p_info->k * 0);
////		ft_draw_line_down(data, data->p_coord->y + SCALE/2, data->p_coord->x +
////		SCALE/2, color);
//	if (data->p_info->direction == 'W')
//		data->p_info->k = ft_draw_vector(data, color, data->p_info->k);
////		ft_draw_line_left(data, data->p_coord->y + SCALE/2, data->p_coord->x +
////		SCALE/2, color);
//	if (data->p_info->direction == 'E')
//		data->p_info->k = ft_draw_vector(data, color, 3 * data->p_info->k);
//}
//
//void move_player_up(t_data *data)
//{
//	if (data->p_info->arr[(int)((data->p_coord->y + SCALE/2 - 2)/SCALE)][(int)
//		((data->p_coord->x + SCALE/2)/SCALE)] == '1')
//		return ;
//	data->p_info->k = ft_draw_vector(data, 0x000000, data->p_info->k);
////	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
////							data->p_addres->img, 0, 0);
////	mlx_clear_window(data->p_draw->mlx, data->p_draw->win);
//	data->p_coord->y -= 2;
//	data->p_info->k = ft_draw_vector(data, 0x00FF00, data->p_info->k);
//	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
//							data->p_addres->img, 0, 0);
//}
//
//void move_player_down(t_data *data)
//{
//	if (data->p_info->arr[(int)((data->p_coord->y + SCALE/2 + 2)/SCALE)][(int)
//	((data->p_coord->x + SCALE/2)/SCALE)] == '1')
//		return ;
//	data->p_info->k = ft_draw_vector(data, 0x000000, data->p_info->k);
////	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
////							data->p_addres->img, 0, 0);
////mlx_clear_window(data->p_draw->mlx, data->p_draw->win);
//	data->p_coord->y+=2;
//	data->p_info->k = ft_draw_vector(data, 0x00FF00, data->p_info->k);
//	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
//							data->p_addres->img, 0, 0);
//}
//
//void move_player_right(t_data *data)
//{
//	if (data->p_info->arr[(int)((data->p_coord->y + SCALE/2)/SCALE)][(int)
//	((data->p_coord->x + SCALE/2 + 2)/SCALE)] == '1')
//		return ;
//	data->p_info->k = ft_draw_vector(data, 0x000000, data->p_info->k);
////	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
////							data->p_addres->img, 0, 0);
////	mlx_clear_window(data->p_draw->mlx, data->p_draw->win);
//	data->p_coord->x += 2;
//	data->p_info->k = ft_draw_vector(data, 0x00FF00, data->p_info->k);
//	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
//							data->p_addres->img, 0, 0);
//
//}
//
//void move_player_left(t_data *data)
//{
//	if (data->p_info->arr[(int)((data->p_coord->y + SCALE/2)/SCALE)][(int)
//	((data->p_coord->x + SCALE/2 - 2)/SCALE)] == '1')
//		return ;
//	data->p_info->k = ft_draw_vector(data, 0x000000, data->p_info->k);
////	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
////							data->p_addres->img, 0, 0);
////mlx_clear_window(data->p_draw->mlx, data->p_draw->win);
//	data->p_coord->x-=2;
//	data->p_info->k = ft_draw_vector(data, 0x000FF00, data->p_info->k);
//	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
//							data->p_addres->img, 0, 0);
//}
//
//void ft_arrow_right(t_data *data)
//{
//	data->p_info->k = ft_draw_vector(data, 0x000000, data->p_info->k);
////	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
////							data->p_addres->img, 0, 0);
//	data->p_info->k = data->p_info->k + M_PI/50;
//	data->p_info->k = ft_draw_vector(data, 0xFFFF00, data->p_info->k);
//	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
//							data->p_addres->img, 0, 0);
//}
//
//void ft_arrow_left(t_data *data)
//{
//	ft_draw_vector(data, 0x000000, data->p_info->k);
////	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
////							data->p_addres->img, 0, 0);
//	data->p_info->k = data->p_info->k - M_PI/50;
//	ft_draw_vector(data, 0xFFFF00, data->p_info->k);
//	mlx_put_image_to_window(data->p_draw->mlx, data->p_draw->win,
//							data->p_addres->img, 0, 0);
//}

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

//int array_hook(int keycode, t_data *data)
//{
//	if (keycode == 124)
//		ft_arrow_right(data);
//
//	return (0);
//}

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
		data->p_coord->vecX = 0;
		data->p_coord->vecY = -1;
	}
	else if (data->p_info->direction == 'S')
	{
		data->p_coord->vecX = 0;
		data->p_coord->vecY = 1;
	}
	else if (data->p_info->direction == 'W')
	{
		data->p_coord->vecX = 1;
		data->p_coord->vecY = 0;
	}
	else if (data->p_info->direction == 'E')
	{
		data->p_coord->vecX = -1;
		data->p_coord->vecY = 0;
	}
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
//	data->p_coord->x *= SCALE;//берем масшабируем координаты
//	data->p_coord->y *= SCALE;//берем масшабируем координаты
//	data->p_coord->x_ray = (float)(data->p_coord->x + SCALE/2);
//	data->p_coord->y_ray = (float)(data->p_coord->y + SCALE/2);
//	print_draw(data);//печать хранимого в data

	ft_draw_3d(data); //рисовка в 3D
	//	ft_draw_map(data); // рисовка самой 2д карты

//	data->p_info->k = M_PI_2; // угол на который нужно повернуть лучи на начальном этапе
//	ft_draw_ray(data, 0x00FF00);

//	mlx_hook(data->p_draw->win, 2, 0, key_hook, data);//нажатие на клавиши wasd
//	mlx_hook(data->p_draw->win, 17, 0, close_win, data);// нажатие на крестик окна
	mlx_loop(data->p_draw->mlx);
//	exit(1);
}
