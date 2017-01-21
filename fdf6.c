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
	//printf("Finding color for Z of %f\n", z);
	pos_scale = map->max_z;
	neg_scale = map->min_z;
	//scale = (map->max_z - map->min_z);
	//printf("Min_z is %d, max_z is %d\n", map->min_z, map->max_z);
	if (z < 0) // since Z is negative, it will still add
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
	//printf("R of %d G of %d B of %d, total %i\n", r, g, b, (r * 0x10000) + (g * 0x100) + b);
	//printf("min was %f and max was %f\n", neg_scale, pos_scale);
	return ((r * 0x10000) + (g * 0x100) + b);
}