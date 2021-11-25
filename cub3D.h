/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erichell <erichell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:06:18 by                   #+#    #+#             */
/*   Updated: 2021/11/25 17:03:01 by erichell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define SCALE 8.0
# define TEXTURES 4

typedef struct s_ptr
{
	int		*ptr;
}	t_ptr;

typedef struct s_tex
{
	int		texdir;
	int		start;
	int		end;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
	double	wallx;
	double	step;
	int		line_height;
	int		texx;
	int		texy;
	double	tex_pos;
	int		*tex_size;
}				t_tex;

typedef struct s_draw {
	void	*mlx;
	void	*win;
	char	*path_n;
	char	*path_s;
	char	*path_w;
	char	*path_e;
	int		f_red;
	int		f_green;
	int		f_blue;
	int		c_red;
	int		c_green;
	int		c_blue;
	void	*img_n;
	void	*img_s;
	void	*img_w;
	void	*img_e;
	int		f_color;
	int		c_color;
	t_ptr	*tex[TEXTURES];
	t_tex	*texture;
}				t_draw;

typedef struct s_addres {
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
	double	vec_x;
	double	vec_y;
	double	angle;
	double	plane_x;
	double	plane_y;
	double	ray_vec_x;
	double	ray_vec_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	move_speed;
	double	rot_speed;
	int		draw_start;
	int		draw_end;
	int		side;
}	t_coord;

typedef struct s_info
{
	int		flag;
	char	**arr;
	int		screen_width;
	int		screen_height;
	int		width;
	int		height;
	char	direction;
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

/* draw.c */
void	ft_draw_general(t_data *data);
void	ft_error(t_data *data);

/* map_cub2d.c */

void	my_pixel_put(t_data *data, int x, int y, int color);
void	ft_draw_map(t_data *data);
int		create_trgb(int t, int r, int g, int b);

/* move.c */
int		key_press(int keycode, t_data *data);
int		close_win(t_data *data);

/* textures.c */
void	textures(t_data *data);
int		init_textures(t_data *data);
void	set_texture(t_data *data);
void	ft_draw_texture(t_data *data, int x, int y);
int		ft_draw_3d(t_data *data);

/* draw_3d.c */
int		ft_draw_3d(t_data *data);
void	ft_draw_general(t_data *data);
void	ft_init_vectors(t_data *data, int x);
void	ft_init_dist(t_data *data);
void	perpwall(t_data *data);
void	ft_dist_wall(t_data *data);

#endif //CUB3D_H