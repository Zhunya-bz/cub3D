/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:30:04 by                   #+#    #+#             */
/*   Updated: 2021/11/01 14:41:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	print_draw(t_data *data)
{
	int	i;

	i = 0;
	printf("width %d\n", data->p_info->width);
	printf("height %d\n", data->p_info->height);
	printf("F_red %d\n", data->p_draw->F_red);
	printf("F_green %d\n", data->p_draw->F_green);
	printf("F_blue %d\n", data->p_draw->F_blue);
	printf("C_red %d\n", data->p_draw->C_red);
	printf("C_green %d\n", data->p_draw->C_green);
	printf("C_blue %d\n", data->p_draw->C_blue);
	printf("path_E %s\n", data->p_draw->path_E);
	printf("y=%f\n", data->p_coord->y);
	while (i < data->p_info->height)
		printf("%s\n", data->p_info->arr[i++]);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.p_draw = malloc(sizeof(t_draw));
	data.p_coord = malloc(sizeof(t_coord));
	data.p_addres = malloc(sizeof(t_addres));
	data.p_info = malloc(sizeof(t_info));
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
			ft_putendl_fd("Error", 1);
			return (1);
		}
		ft_draw_cub2d(&data);
	}
	free_all(&data);
	while (1);
	return (0);
}
