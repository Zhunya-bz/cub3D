/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_before_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:28:57 by                   #+#    #+#             */
/*   Updated: 2021/11/25 15:57:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
		ft_path(&data->p_draw->path_n, line);
	else if (line[0] == 'S' && line[1] == 'O')
		ft_path(&data->p_draw->path_s, line);
	else if (line[0] == 'W' && line[1] == 'E')
		ft_path(&data->p_draw->path_w, line);
	else if (line[0] == 'E' && line[1] == 'A')
		ft_path(&data->p_draw->path_e, line);
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
