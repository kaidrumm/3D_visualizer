/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrumm <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 21:53:40 by kdrumm            #+#    #+#             */
/*   Updated: 2016/12/01 21:53:42 by kdrumm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_pt
{
	double		x;
	double		y;
	double		z;
	double		raw_x;
	double		raw_y;
	double		raw_z;
	double		view_x;
	double		view_y;
	int			color;
}				t_pt;

typedef struct	s_map
{
	void		*cnx;
	void		*win;
	void		*img;
	char		*addr;
	t_pt		***dots;
	int			w;
	int			h;
	int			max_x;
	int			max_y;
	int			min_z;
	int			max_z;
	int			bpp;
	int			bpl;
	int			endian;
	int			image_option;
}				t_map;

// FDF 6: Color
int				set_color(t_map *map, double z);

// FDF 2: Drawing
void			draw_pixel(t_map *map, int x, int y, double z);
void			draw_line_v(t_pt *a, t_pt *b, t_map *map);
void			draw_line_h(t_pt *a, t_pt *b, t_map *map);
void			draw_line(t_pt *a, t_pt *b, t_map *map);
void			print_dots(t_map *map);

// FDF 4: Hook
void			helptext(t_map *map);
int				mouse_hook(int button, int x, int y, t_map *map);
int				expose_hook(t_map *map);
int				key_hook2(int keycode, t_map *map);
int				key_hook(int keycode, t_map *map);

// FDF 3: Rotation
void			project_perspective(t_map *map);
void			rotate_z(t_map *map, double theta);
void			rotate_x(t_map *map, double theta);
void			rotate_y(t_map *map, double theta);

// FDF 5: Scaling & Centering
void			center_screen(t_map *map);
void			center(t_map *map);
void			scale(t_map *map, double o);
void			zoom(t_map *map, double o);
void			reset(t_map *map);

// FDF 1: Setup
t_pt			*new_point(int x, int y, int z);
void			start_window(t_map *map);
void			read_file(int fd, t_map *map);
void			init_map(t_map **map);

#endif
