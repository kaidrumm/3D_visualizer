/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrumm <kdrumm@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 19:24:55 by kdrumm            #+#    #+#             */
/*   Updated: 2017/01/12 19:24:57 by kdrumm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		sign(int x)
{
	if (x > 0)
		return (1);
	else if (x < 0)
		return (-1);
	else
		return (0);
}

/*
** I wrote this with the idea that it would provide a green gradient.
** It starts at bright green. Positive numbers add to R and B until white.
** Negative numbers sutract from all colors until black.
** Max pos should be (240, 20, 0)
** Max neg should be (42, 240, 40)
*/

int		set_color(t_map *map, double z)
{
	int		r;
	int		g;
	int		b;
	double	pos_scale;
	double	neg_scale;

	r = 0xff;
	g = 0xff;
	b = 0xff;
	pos_scale = map->max_z;
	neg_scale = map->min_z;
	if (z < 0)
	{
		r -= (int)round(z * 215 / neg_scale);
		g -= (int)round(z * 15 / neg_scale);
		b -= (int)round(z * 215 / neg_scale);
	}
	else if (z > 0)
	{
		r -= (int)round(z * 15 / pos_scale);
		g -= (int)round(z * 215 / pos_scale);
		b -= (int)round(z * 15 / pos_scale);
	}
	return ((r * 0x10000) + (g * 0x100) + b);
}

int		helptext(t_map *map, int c, int (*f)(void *, void *, int, int, int,
	char *))
{
	mlx_clear_window(map->cnx, map->win);
	f(map->cnx, map->win, 10, 10, c, "Welcome to FDF by KaiDrumm!");
	f(map->cnx, map->win, 10, 30, c, "Press H to return to helptext.");
	f(map->cnx, map->win, 10, 50, c, "Spacebar will reset the image to its \
		initial position.");
	f(map->cnx, map->win, 10, 70, c, "Press ESC to exit (but you know you \
		don't want to)");
	f(map->cnx, map->win, 10, 90, c, "Most controls are on the numpad.");
	f(map->cnx, map->win, 10, 110, c, "Plus and minus will zoom in and out");
	f(map->cnx, map->win, 10, 130, c, "* and / will scale the Z axis for you,");
	f(map->cnx, map->win, 10, 150, c, "= will flip the Z axis entirely.");
	f(map->cnx, map->win, 10, 170, c, "Numpad keys make it rotate. Use 7 and 8 \
		for X axis, 4 and 5 for Y, 1 and 2 for Z.");
	f(map->cnx, map->win, 10, 190, c, "Enter will toggle between image setting \
	vs pixel setting.");
	f(map->cnx, map->win, 10, 210, c, "On the number row, press 1 for \
		isometric projection, or 2 for perspective.");
	f(map->cnx, map->win, 10, 350, 0xf442a1, "Press any key to begin.");
	return (1);
}

void	reset(t_map *map)
{
	int		i;
	int		j;
	t_pt	*pt;

	j = -1;
	while (map->dots[++j])
	{
		i = -1;
		while (map->dots[j][++i])
		{
			pt = map->dots[j][i];
			pt->x = pt->raw_x;
			pt->y = pt->raw_y;
			pt->z = pt->raw_z;
		}
	}
	map->z_dist = 4 * (map->max_z - map->min_z);
	center(map);
}
