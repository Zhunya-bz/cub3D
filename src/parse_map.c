/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:29:22 by                   #+#    #+#             */
/*   Updated: 2021/11/01 16:15:34 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
			if (data->p_info->arr[i][j] == 'W' || data->p_info->arr[i][j] ==
			'E' ||
			data->p_info->arr[i][j] == 'S' || data->p_info->arr[i][j] == 'N')
			{
				if (data->p_info->flag == 1)
					return (1);
				data->p_info->direction = data->p_info->arr[i][j];
				data->p_coord->x = j;
				data->p_coord->y = i;
				data->p_info->flag = 1;
			}
			else if (!(data->p_info->arr[i][j] == '1' || data->p_info->arr[i][j]
			== '0' ||
			data->p_info->arr[i][j] == ' '))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_parse_map_second(char **argv, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	while ((get_next_line(fd, &line)))
	{
		if (line[0] == ' ' || ft_isdigit(line[0]))
			data->p_info->arr[i++] = line;
		else
			free(line);
	}
	if (line[0] == ' ' || ft_isdigit(line[0]))
		data->p_info->arr[i++] = line;
	else
		free(line);
	close(fd);
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

static int	ft_check_map_border_inside(t_data *data, int *i, int *j)
{
	if (data->p_info->arr[*i][*j - 1] == ' ') //предыдущий в строке
		return (1);
	if (data->p_info->arr[*i][*j + 1] && data->p_info->arr[*i][*j + 1] == ' ')
		// след в
		// строке
		return (1);
	if (*i - 1 < 0 || *i + 1 >= data->p_info->height || *j - 1 < 0 || *j + 1
		>= ft_strlen(data->p_info->arr[*i]))
		return (1);
	if (!data->p_info->arr[*i - 1][*j] || data->p_info->arr[*i - 1][*j] ==' ')
		// сверху над
		// строкой
		return (1);
	if (!data->p_info->arr[*i + 1][*j] || data->p_info->arr[*i + 1][*j] == ' ')
		// снизу над
		// строкой
		return (1);
	if (!data->p_info->arr[*i - 1][*j - 1] || data->p_info->arr[*i - 1][*j - 1]
	== ' ') //
		// угловой слева вверх
		return (1);
	if (!data->p_info->arr[*i - 1][*j + 1] || data->p_info->arr[*i - 1][*j +
	1]
	== ' ') //
		// угловой справа вверх
		return (1);
	if (!data->p_info->arr[*i + 1][*j - 1] || data->p_info->arr[*i + 1][*j - 1]
	== ' ') //
		// угловой слева низ
		return (1);
	if (!data->p_info->arr[*i + 1][*j + 1] || data->p_info->arr[*i + 1][*j + 1]
	== ' ') //
		// угловой справа низ
		return (1);
	return (0);
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
				if (ft_check_map_border_inside(data, &i, &j))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
