/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_before_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:28:57 by                   #+#    #+#             */
/*   Updated: 2021/10/16 17:28:57 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

static void	ft_path(char **str, char *line)
{
	int	i;

	i = 2;
	while (line[i] == ' ')
		i++;
	*str = ft_strdup(&line[i]);
}

int	ft_parser_help(t_data *data, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		ft_path(&data->p_draw->path_N, line);
	else if (line[0] == 'S' && line[1] == 'O')
		ft_path(&data->p_draw->path_S, line);
	else if (line[0] == 'W' && line[1] == 'E')
		ft_path(&data->p_draw->path_W, line);
	else if (line[0] == 'E' && line[1] == 'A')
		ft_path(&data->p_draw->path_E, line);
	else if (ft_strcmp(line, "") == 0)
		return (0);
	else if (line[0] == 'F')
	{
		if (ft_color_floor(line, data->p_draw))
			return (1);
	}
	else if (line[0] == 'C')
	{
		if (ft_color_ceiling(line, data->p_draw))
			return (1);
	}
	else if (line[0] == ' ' || ft_isdigit(line[0]))
		ft_map_count(line, data);
	else
		return (1);
	return (0);
}
