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
	int			z_dist;
	int			z_scale;
	int			bpp;
	int			bpl;
	int			endian;
	char		image_option;
	char		projection_option;
	int			tile_w;
	int			tile_h;
}				t_map;

/*
** FDF 6: Extra funk-tions
*/

int				sign(int x);
int				set_color(t_map *map, double z);
int				helptext(t_map *map, int c, int (*f)(void *, void *, int,
					int, int, char *));
void			reset(t_map *map);

/*
** FDF 5: Scaling & Centering
*/

void			center_screen(t_map *map);
void			center(t_map *map);
void			scale(t_map *map, double o);
void			zoom_control(t_map *map, double o);
void			zoom(t_map *map, double o);

/*
** FDF 4: Hook
*/

int				mouse_hook(void);
int				expose_hook(t_map *map);
int				key_hook2(int keycode, t_map *map);
int				key_hook(int keycode, t_map *map);
void			display(t_map *map);

/*
** FDF 3: Rotation
*/

void			project_isometric(t_map *map);
void			project_perspective(t_map *map);
void			rotate_z(t_map *map, double theta);
void			rotate_x(t_map *map, double theta);
void			rotate_y(t_map *map, double theta);

/*
** FDF 2: Drawing
*/

void			draw_pixel(t_map *map, int x, int y, double z);
void			bresenham_pt2(t_map *map, double *z, int *ints);
void			bresenham_pt1(t_map *map, t_pt *a, t_pt *b);
void			draw_line(t_pt *a, t_pt *b, t_map *map);
void			print_dots(t_map *map);

/*
** FDF 1: Setup
*/

t_pt			*new_point(int x, int y, int z);
void			z_limits(t_map *map, int x);
int				read_file(int fd, t_map *map);
int				init_map(t_map **map);
int				main(int ac, char **av);

#endif
