#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "math.h"
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
	int 	F_color;
	int 	C_color;
}				t_draw;

typedef struct	s_addres {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_addres;

typedef struct s_coord
{
	double	x;
	double	y;
	double	vecX;
	double	vecY;
	double planeX; // =0
	double planeY; // =0.66
	double	ray_vecX;
	double	ray_vecY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int 	mapX;
	int 	mapY;
	int		stepX;
	int		stepY;
}	t_coord;

typedef struct s_info
{
	int 		flag;
	char		**arr;
	int 		screen_width;
	int 		screen_height;
	int			width;
	int			height;
	char		direction;
	float 		k;
	float		pov; // point of view-точка зрения
	float 		dist;
}	t_info;

typedef struct s_data
{
	t_draw		*p_draw;
	t_coord		*p_coord;
	t_addres	*p_addres;
	t_info		*p_info;
}	t_data;

/* parser */

int		get_next_line(int fd, char **line);
int		ft_parser(char **argv, t_data *data);
int		ft_parser_help(t_data *data, char *line);
int		ft_color_ceiling(char *line, t_draw *draw);
int		ft_color_floor(char *line, t_draw *draw);
int		ft_check_map_char(t_data *data);
void	ft_map_count(char *line, t_data *data);
int		ft_check_map_border(t_data *data);
int		ft_check_cub(char **argv);
void	free_all(t_data *data);
void	ft_draw_cub2d(t_data *data);
void	print_draw(t_data *data);

void	my_pixel_put(t_data *data, int x, int y, int color);
void	ft_draw_map(t_data *data);
int		ft_draw_3d(t_data *data);

#endif //CUB3D_H