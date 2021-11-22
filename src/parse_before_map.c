/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_before_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:28:57 by                   #+#    #+#             */
/*   Updated: 2021/11/22 18:28:35 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	ft_path(char **str, char *line)
{
	int	i;

	i = 2;
	while (line[i] == ' ')
		i++;
	if (!(*str))
	{
		*str = ft_strdup(&line[i]);
		if (!(*str))
			return (1);
	}
	else
		return (1);
	return (0);
}

int	ft_parser_help(t_data *data, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (ft_path(&data->p_draw->path_N, line));
	else if (line[0] == 'S' && line[1] == 'O')
		return (ft_path(&data->p_draw->path_S, line));
	else if (line[0] == 'W' && line[1] == 'E')
		return (ft_path(&data->p_draw->path_W, line));
	else if (line[0] == 'E' && line[1] == 'A')
		return (ft_path(&data->p_draw->path_E, line));
	else if (ft_strcmp(line, "") == 0)
		return (0);
	else if (line[0] == 'F')
		return (ft_color_floor(line, data->p_draw));
	else if (line[0] == 'C')
		return (ft_color_ceiling(line, data->p_draw));
	else if (line[0] == ' ' || ft_isdigit(line[0]))
		ft_map_count(line, data);
	else
	{
		return (1);
	}
	return (0);
}
