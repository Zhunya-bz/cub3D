/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:30:04 by                   #+#    #+#             */
/*   Updated: 2021/11/25 15:47:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	init_struct(t_data *data)
{
	data->p_draw = malloc(sizeof(t_draw));
	data->p_coord = malloc(sizeof(t_coord));
	data->p_addres = malloc(sizeof(t_addres));
	data->p_info = malloc(sizeof(t_info));
	if (!data->p_draw || !data->p_addres || !data->p_coord)
	{
		ft_putendl_fd("Error malloc", 1);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Error", 1);
		return (1);
	}
	else
	{
		if (init_struct(&data))
			return (1);
		if (ft_parser(argv, &data))
			ft_error(&data);
		ft_draw_general(&data);
	}
	free_all(&data);
	return (0);
}
