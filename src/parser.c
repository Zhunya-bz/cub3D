/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:21:16 by                   #+#    #+#             */
/*   Updated: 2021/10/16 17:34:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	init_draw(t_data *data)
{
	data->width = 0;
	data->height = 0;
	data->direction = '\0';
	data->p_coord->x = -1;
	data->p_coord->y = -1;
	data->p_draw->F_red = -1;
	data->p_draw->F_green = -1;
	data->p_draw->F_blue = -1;
	data->p_draw->C_red = -1;
	data->p_draw->C_blue = -1;
	data->p_draw->C_green = -1;
}

static void	print_draw(t_data *data)
{
	int	i;

	i = 0;
	printf("width %d\n", data->width);
	printf("height %d\n", data->height);
	printf("F_red %d\n", data->p_draw->F_red);
	printf("F_green %d\n", data->p_draw->F_green);
	printf("F_blue %d\n", data->p_draw->F_blue);
	printf("C_red %d\n", data->p_draw->C_red);
	printf("C_green %d\n", data->p_draw->C_green);
	printf("C_blue %d\n", data->p_draw->C_blue);
	printf("path_E %s\n", data->p_draw->path_E);
	while (i < data->height)
		printf("%s\n", data->arr[i++]);
}

static void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		free(data->arr[i]);
		i++;
	}
	free(data->arr);
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

int	ft_parser(char **argv)
{
	t_data	data;
	t_draw	draw;
	t_coord	coord;
	char	*line;

	line = NULL;
	data.p_draw = &draw;
	data.p_coord = &coord;
	init_draw(&data);
	if (ft_parse_gnl(&data, argv, line))
		return (1);
	data.arr = (char **)malloc(sizeof(char *) * (data.height + 1));
	data.arr[data.height] = NULL;
	if (ft_parse_map_second(argv, &data) || ft_check_map_char(&data)
		|| ft_check_map_border(&data))
	{
		free_all(&data);
		return (1);
	}
	print_draw(&data);
	free_all(&data);
	return (0);
}
