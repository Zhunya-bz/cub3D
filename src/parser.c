/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:21:16 by                   #+#    #+#             */
/*   Updated: 2021/11/09 13:01:52 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	init_draw(t_data *data)
{
	data->p_info->width = 0;
	data->p_info->height = 0;
	data->p_info->screen_height = 720;
	data->p_info->screen_width = 1280;
	data->p_info->direction = '\0';
	data->p_coord->x = -1;
	data->p_coord->y = -1;
	data->p_draw->F_red = -1;
	data->p_draw->F_green = -1;
	data->p_draw->F_blue = -1;
	data->p_draw->C_red = -1;
	data->p_draw->C_blue = -1;
	data->p_draw->C_green = -1;
	data->p_draw->path_E = NULL;
	data->p_draw->path_W = NULL;
	data->p_draw->path_N = NULL;
	data->p_draw->path_S = NULL;
	data->p_info->dist = 0;
	data->p_info->pov = 0;
	data->p_info->flag = 0;
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_info->height)
	{
		free(data->p_info->arr[i]);
		i++;
	}
	free(data->p_info->arr);
	free(data->p_draw->path_E);
	free(data->p_draw->path_W);
	free(data->p_draw->path_S);
	free(data->p_draw->path_N);
}

static void	ft_free_close(char *line, int fd)
{
	free(line);
	close(fd);
}

static int	ft_parse_gnl(t_data *data, char **argv, char *line)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	while ((get_next_line(fd, &line)))
	{
		if (ft_parser_help(data, line))
		{
			ft_free_close(line, fd);
			return (1);
		}
		free(line);
	}
	if (line[0] == ' ' || ft_isdigit(line[0]))
		ft_map_count(line, data);
	else if ((ft_strcmp(line, "\0") != 0))
	{
		ft_free_close(line, fd);
		return (1);
	}
	ft_free_close(line, fd);
	return (0);
}

int ft_check_cub(char **argv)
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

int	ft_parser(char **argv, t_data *data)
{
	char	*line;

	line = NULL;
	init_draw(data);
	if (ft_check_cub(argv) || ft_parse_gnl(data, argv, line))
		return (1);
	data->p_info->arr = (char **)malloc(sizeof(char *) * (data->p_info->height +1));
	data->p_info->arr[data->p_info->height] = NULL;
	if (ft_parse_map_second(argv, data) || ft_check_map_char(data)
		|| ft_check_map_border(data) || data->p_info->direction == '\0'
		|| data->p_coord->y == -1 || data->p_coord->x == -1)
	{
//		print_draw(data); // delete
		free_all(data);
		return (1);
	}
//	print_draw(data);
//	free_all(data);
	return (0);
}
