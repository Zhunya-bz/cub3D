/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:05:56 by                   #+#    #+#             */
/*   Updated: 2021/11/22 18:05:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_info->height)
	{
		if (data->p_info->arr[i])
			free(data->p_info->arr[i]);
		i++;
	}
	if (data->p_info->arr)
		free(data->p_info->arr);
	if (data->p_draw->path_E)
		free(data->p_draw->path_E);
	if (data->p_draw->path_W)
		free(data->p_draw->path_W);
	if (data->p_draw->path_S)
		free(data->p_draw->path_S);
	if (data->p_draw->path_N)
		free(data->p_draw->path_N);
	free(data->p_draw);
	free(data->p_info);
	free(data->p_addres);
	free(data->p_coord);
}

int	ft_check_cub(char **argv)
{
	int		i;
	char	*str;

	i = 0;
	while (argv[1][i] != '.')
		i++;
	str = ft_strdup(&argv[1][i]);
	if (ft_strcmp(str, ".cub"))
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

static unsigned long	ft_help_color(char *line, int *i)
{
	unsigned long	res;

	res = 0;
	(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	while (line[*i] && ft_isdigit(line[*i]))
	{
		res = res * 10 + line[*i] - '0';
		(*i)++;
	}
	if (res < 0 || res > 255 || (line[*i] != ',' && line[*i] != '\0'))
		return (-1);
	return (res);
}

int	ft_color_floor(char *line, t_draw *draw)
{
	int	i;

	i = 0;
	draw->F_red = ft_help_color(line, &i);
	draw->F_green = ft_help_color(line, &i);
	draw->F_blue = ft_help_color(line, &i);
	if (draw->F_red < 0 || draw->F_green < 0 || draw->F_blue < 0)
		return (1);
	return (0);
}

int	ft_color_ceiling(char *line, t_draw *draw)
{
	int	i;

	i = 0;
	draw->C_red = ft_help_color(line, &i);
	draw->C_green = ft_help_color(line, &i);
	draw->C_blue = ft_help_color(line, &i);
	if (draw->C_red < 0 || draw->C_green < 0 || draw->C_blue < 0)
		return (1);
	return (0);
}
