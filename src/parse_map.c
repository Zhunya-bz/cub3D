/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:29:22 by                   #+#    #+#             */
/*   Updated: 2021/11/25 14:12:41 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	ft_check_map_border_inside(t_data *data, int i, int j)
{
	if (data->p_info->arr[i][j - 1] == ' ')
		return (1);
	if (data->p_info->arr[i][j + 1] && data->p_info->arr[i][j + 1] == ' ')
		return (1);
	if (i - 1 < 0 || i + 1 >= data->p_info->height || j - 1 < 0 || j + 1
		>= ft_strlen(data->p_info->arr[i]))
		return (1);
	if (!data->p_info->arr[i - 1][j] || data->p_info->arr[i - 1][j] == ' ')
		return (1);
	if (!data->p_info->arr[i + 1][j] || data->p_info->arr[i + 1][j] == ' ')
		return (1);
	if (!data->p_info->arr[i - 1][j - 1] || data->p_info->arr[i - 1][j - 1]
		== ' ')
		return (1);
	if (!data->p_info->arr[i - 1][j + 1] || data->p_info->arr[i - 1][j + 1]
		== ' ')
		return (1);
	if (!data->p_info->arr[i + 1][j - 1] || data->p_info->arr[i + 1][j - 1]
		== ' ')
		return (1);
	if (!data->p_info->arr[i + 1][j + 1] || data->p_info->arr[i + 1][j + 1]
		== ' ')
		return (1);
	return (0);
}

static int	ft_check_player(t_data *data, int i, int j)
{
	if (data->p_info->arr[i][j] == 'W' || data->p_info->arr[i][j] == 'E' ||
		data->p_info->arr[i][j] == 'S' || data->p_info->arr[i][j] == 'N')
	{
		if (data->p_info->flag == 1)
			return (1);
		data->p_info->direction = data->p_info->arr[i][j];
		data->p_coord->x = j;
		data->p_coord->y = i;
		if (ft_check_map_border_inside(data, data->p_coord->y,
				data->p_coord->x))
			return (1);
		data->p_info->flag = 1;
	}
	else if (!(data->p_info->arr[i][j] == '1' || data->p_info->arr[i][j]
		== '0' || data->p_info->arr[i][j] == ' '))
		return (1);
	return (0);
}

int	ft_check_map_char(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->p_info->arr[i])
	{
		j = 0;
		while (data->p_info->arr[i][j])
		{
			if (ft_check_player(data, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_map_count(char *line, t_data *data)
{
	int	count;

	count = ft_strlen(line);
	if (count > data->p_info->width)
		data->p_info->width = count;
	data->p_info->height++;
}

int	ft_check_map_border(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->p_info->arr[i])
	{
		j = 0;
		while (data->p_info->arr[i][j])
		{
			if (data->p_info->arr[i][j] == '0')
			{
				if (ft_check_map_border_inside(data, i, j))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
