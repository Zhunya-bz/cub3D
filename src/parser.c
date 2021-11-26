/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltmer <saltmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:21:16 by                   #+#    #+#             */
/*   Updated: 2021/11/26 11:46:48 by saltmer          ###   ########.fr       */
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
	data->p_coord->vec_x = 0;
	data->p_coord->vec_y = 0;
	data->p_coord->angle = 0.66;
	data->p_coord->ray_vec_x = 0;
	data->p_coord->ray_vec_y = 0;
	data->p_coord->move_speed = 0.2;
	data->p_coord->rot_speed = M_PI / 32;
	data->p_draw->f_red = -1;
	data->p_draw->f_green = -1;
	data->p_draw->f_blue = -1;
	data->p_draw->c_red = -1;
	data->p_draw->c_blue = -1;
	data->p_draw->c_green = -1;
	data->p_draw->path_e = NULL;
	data->p_draw->path_w = NULL;
	data->p_draw->path_n = NULL;
	data->p_draw->path_s = NULL;
	data->p_info->flag = 0;
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

static int	ft_parse_map_second(char **argv, t_data *data)
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

int	ft_parser(char **argv, t_data *data)
{
	char	*line;

	line = NULL;
	data->p_info->arr = NULL;
	init_draw(data);
	if (ft_check_cub(argv) || ft_parse_gnl(data, argv, line))
		return (1);
	data->p_info->arr = (char **)malloc(sizeof(char *)
			* (data->p_info->height + 1));
	data->p_info->arr[data->p_info->height] = NULL;
	if (ft_parse_map_second(argv, data) || ft_check_map_char(data)
		|| ft_check_map_border(data) || data->p_info->direction == '\0'
		|| data->p_coord->y == -1 || data->p_coord->x == -1)
		return (1);
	return (0);
}
