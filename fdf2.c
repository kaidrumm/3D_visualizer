/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrumm <kdrumm@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:08:05 by kdrumm            #+#    #+#             */
/*   Updated: 2016/12/14 17:08:06 by kdrumm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(t_map *map, int x, int y, double z)
{
	int		color;
	char	*addr;

	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return ;
	color = set_color(map, z);
	if (map->image_option == 1)
	{
		addr = &(map->addr[((map->bpp) * x / 8) + ((map->bpl) * y)]);
		ft_memcpy(addr, &color, (map->bpp) / 8);
	}
	else
		mlx_pixel_put(map->cnx, map->win, x, y, 0Xd56497);
}

void	bresenham_retry(t_map *map, int ax, int ay, double az, int bx, int by, double bz)
{
	int		x;
	int		y;
	double	z;
	int		dx;
	int		dy;
	double	dz;
	int		sx;
	int		sy;
	int		sz;
	int		err;
	int		swap;
	int		i;

	y = ay;
	x = ax;
	z = az;
	dx = ABS(bx - ax);
	dy = ABS(by - ay);
	dz = ABS(bz - az);
	sx = sign(bx - ax);
	sy = sign(by - ay);
	sz = sign(bz - az);
	err = ABS(dy - dx);
	swap = 0;
	if (dy > dx)
	{
		swap = 1;
		dz = dz * sz / (double)(dy);
		ft_swap(&dx, &dy);
	}
	else
		dz = dz * sz / (double)(dx);
	i = 0;
	while (i++ <= dx)
	{
		draw_pixel(map, x, y, z);
		if (err >= 0)
		{
			if (swap)
				x += sx;
			else
				y += sy;
			err -= dx;
		}
		if (swap)
			y += sy;
		else
			x += sx;
		err += dy;
		z += dz;
	}
}

/*
** At this point we should check if the line is totally out of range of the image view.
*/

void	draw_line(t_pt *a, t_pt *b, t_map *map)
{
	if ((a->view_x < 0 && b->view_x < 0) || (a->view_x > map->w && b->view_x > map->w)
		|| (a->view_y < 0 && b->view_y < 0) || (a->view_y > map->h && b->view_y > map->h))
		return ;
	bresenham_retry(map, (int)round(a->view_x), (int)round(a->view_y), a->raw_z,
		(int)round(b->view_x), (int)round(b->view_y), b->raw_z);
}

void	print_dots(t_map *map)
{
	int		i;
	int		j;

	center_screen(map);
	j = -1;
	while (map->dots[++j] != NULL)
	{
		i = -1;
		while (map->dots[j][++i] != NULL)
		{
			if (map->dots[j][i + 1] != NULL)
				draw_line(map->dots[j][i], map->dots[j][i + 1], map);
			if (map->dots[j + 1] && map->dots[j + 1][i] != NULL)
				draw_line(map->dots[j][i], map->dots[j + 1][i], map);
		}
	}
}
