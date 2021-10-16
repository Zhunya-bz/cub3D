#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <stddef.h>

typedef struct s_draw {
	void	*mlx;
	void	*win;
	char	*path_N;
	char	*path_S;
	char	*path_W;
	char	*path_E;
//	int		img_w;
//	int		img_h;
//	int		arr_h;
//	int		arr_w;
	int 	F_red;
	int 	F_green;
	int 	F_blue;
	int 	C_red;
	int 	C_green;
	int 	C_blue;
	void	*img_N;
	void	*img_S;
	void	*img_W;
	void	*img_E;
}				t_draw;

typedef struct s_coord
{
	int 	x;
	int 	y;
}	t_coord;

typedef struct s_data
{
	t_draw	*p_draw;
	t_coord *p_coord;
	char	**arr;
	int		width;
	int		height;
	char 	direction;
}	t_data;

int		get_next_line(int fd, char **line);
int		ft_parser(char **argv);
int		ft_parser_help(t_data *data, char *line);
int		ft_color_ceiling(char *line, t_draw *draw);
int		ft_color_floor(char *line, t_draw *draw);
int		ft_check_map_char(t_data *data);
int		ft_parse_map_second(char **argv, t_data *data);
void	ft_map_count(char *line, t_data *data);
int		ft_check_map_border(t_data *data);

#endif //CUB3D_H