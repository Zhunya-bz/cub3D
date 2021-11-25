#include "../cub3D.h"

static void textures(t_data *data)
{
	
	int size;
	int i;

	size = 64;
	i = -1;
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
	while (++i < TEXTURES)
	{
		data->p_draw->tex[i] = NULL;
		data->p_draw->tex[i] = malloc(sizeof(t_ptr));
		
	}
	data->p_draw->texture = malloc(sizeof(t_tex));
	data->p_draw->texture->height = 64;
	data->p_draw->texture->width = 64;
	data->p_draw->texture->bpp = 8;
	data->p_draw->texture->size_line = 64;
	data->p_draw->texture->endian = 0;
	data->p_draw->tex[0]->ptr = (int *)mlx_get_data_addr(data->p_draw->img_N, &data->p_draw->texture->bpp, &data->p_draw->texture->size_line, &data->p_draw->texture->endian);
	data->p_draw->tex[1]->ptr = (int *)mlx_get_data_addr(data->p_draw->img_S, &data->p_draw->texture->bpp, &data->p_draw->texture->size_line, &data->p_draw->texture->endian);
	data->p_draw->tex[2]->ptr = (int *)mlx_get_data_addr(data->p_draw->img_W, &data->p_draw->texture->bpp, &data->p_draw->texture->size_line, &data->p_draw->texture->endian);
	data->p_draw->tex[3]->ptr = (int *)mlx_get_data_addr(data->p_draw->img_E, &data->p_draw->texture->bpp, &data->p_draw->texture->size_line, &data->p_draw->texture->endian);
	
}

static void init_direction_vector(t_data *data, double x, double y)
{
	data->p_coord->vecX = x;
	data->p_coord->vecY = y;
}

static void init_direction_camera(t_data *data, double x, double y)
{
	data->p_coord->planeX = x;
	data->p_coord->planeY = y;
}

static void init_colors_vectors(t_data *data)
{
	data->p_draw->F_color = create_trgb(0, data->p_draw->F_red,
										data->p_draw->F_green,data->p_draw->F_blue);//преобразуем цвет пола в HEX
	data->p_draw->C_color = create_trgb(0, data->p_draw->C_red,
										data->p_draw->C_green,data->p_draw->C_blue);//преобразуем цвет неба в HEX
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

void ft_draw_general(t_data *data)
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
	(data->p_coord->x) += .5;
	(data->p_coord->y) += .5;
	ft_draw_3d(data); //рисовка в 3D
	ft_draw_map(data); // рисовка самой 2д карты
	mlx_hook(data->p_draw->win, 2, 0, key_press, data);
	mlx_hook(data->p_draw->win, 17, 0, close_win, data);// нажатие на крестик окна
	mlx_loop(data->p_draw->mlx);
}
