/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:30:04 by                   #+#    #+#             */
/*   Updated: 2021/10/24 14:39:40 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	print_draw(t_data *data)
{
	int	i;

	i = 0;
	printf("width %d\n", data->width);
	printf("height %d\n", data->height);
	printf("F_red %d\n", data->p_draw->F_red);
	printf("F_green %d\n", data->p_draw->F_green);
	printf("F_blue %d\n", data->p_draw->F_blue);
	printf("C_red %d\n", data->p_draw->C_red);
	printf("C_green %d\n", data->p_draw->C_green);
	printf("C_blue %d\n", data->p_draw->C_blue);
	printf("path_E %s\n", data->p_draw->path_E);
	while (i < data->height)
		printf("%s\n", data->arr[i++]);
}

int	main(int argc, char **argv)
{
	t_data	data;
//	t_draw	draw;
//	t_coord	coord;
//	t_addres addres1;

//	data.p_draw= &draw;
//	data.p_coord = &coord;
//	data.p_addres = &addres1;
	data.p_draw = malloc(sizeof(t_draw));
	data.p_coord = malloc(sizeof(t_coord));
	data.p_addres = malloc(sizeof(t_addres));
	if (!data.p_draw || !data.p_addres || !data.p_coord)
	{
		ft_putendl_fd("Error malloc", 1);
		return (1);
	}
	if (argc != 2)
	{
		ft_putendl_fd("Error", 1);
		return (1);
	}
	else
	{
		if (ft_parser(argv, &data))
		{
			ft_putendl_fd("Error2", 1);
			return (1);
		}
//		print_draw(&data);
		ft_draw_cub2d(&data);
	}
	free_all(&data);
	return (0);
}
