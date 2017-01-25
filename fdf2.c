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

void	bresenham_pt2(t_map *map, double *z, int *ints)
{
	ints[9] = 0;
	while (ints[9]++ <= ints[2])
	{
		draw_pixel(map, ints[0], ints[1], z[0]);
		if (ints[7] >= 0)
		{
			if (ints[8])
				ints[0] += ints[4];
			else
				ints[1] += ints[5];
			ints[7] -= ints[2];
		}
		if (ints[8])
			ints[1] += ints[5];
		else
			ints[0] += ints[4];
		ints[7] += ints[3];
		z[0] += z[1];
	}
}

/*
** Bresenham's equation uses more than the 5 variables allowed by Norm.
** Here are the meanings of the arrays:
** z[0] = z; z[1] = dz
** ints[0] = x; ints[1] = y; ints[2] = dx; ints[3] = dy;
** ints[4] = sign_x; ints[5] = sign_y; ints[6] = sign_z; ints[7] = error;
** ints[8] = swap guiding axis flag; ints[9] = i (for the loop)
*/

void	bresenham_pt1(t_map *map, t_pt *a, t_pt *b)
{
	double	z[2];
	int		ints[10];

	ints[1] = (int)round(a->view_y);
	ints[0] = (int)round(a->view_x);
	z[0] = a->raw_z;
	ints[2] = (int)round(ABS(b->view_x - a->view_x));
	ints[3] = (int)round(ABS(b->view_y - a->view_y));
	z[1] = ABS(b->raw_z - a->raw_z);
	ints[4] = sign(b->view_x - a->view_x);
	ints[5] = sign(b->view_y - a->view_y);
	ints[6] = sign(b->raw_z - a->raw_z);
	ints[7] = ABS(ints[3] - ints[2]);
	ints[8] = 0;
	if (ints[3] > ints[2])
	{
		ints[8] = 1;
		z[1] = z[1] * ints[6] / (double)(ints[3]);
		ft_swap(&ints[2], &ints[3]);
	}
	else
		z[1] = z[1] * ints[6] / (double)(ints[2]);
	bresenham_pt2(map, z, ints);
}

/*
** At this point we check if the line is out of range of the image view.
*/

void	draw_line(t_pt *a, t_pt *b, t_map *map)
{
	if ((a->view_x < 0 && b->view_x < 0) || (a->view_x > map->w && b->view_x >
	map->w)
		|| (a->view_y < 0 && b->view_y < 0) || (a->view_y > map->h && b->view_y
		> map->h) || (a->view_x < 0 && b->view_x > map->w) || (b->view_x < 0 &&
		a->view_x > map->w) || (a->view_y < 0 && b->view_y > map->w) ||
		(b->view_y < 0 && a->view_y > map->w))
		return ;
	else if ((a->z + map->z_dist < 0) || (b->z + map->z_dist < 0))
		return ;
	bresenham_pt1(map, a, b);
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
