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

int		set_color(t_map *map, double z)
{
	int		r;
	int		g;
	int		b;
	double	scale;

	r = 42;
	g = 242;
	b = 42;
	scale = (map->max_z - map->min_z);
	printf("Z of %f\n", z);
	//printf("Min_z is %d, max_z is %d, Scale is %f\n", map->min_z, map->max_z, scale);
	if (z < 0)
	{
		r -= (int)round(z * 2 * 40 / scale);
		g -= (int)round(z * 2 * 240 / scale);
		b -= (int)round(z * 2 * 420 / scale);
	}
	if (z > 0)
	{
		r += (int)round(z * 2 * 200 / scale);
		b += (int)round(z * 2 * 200 / scale);
	}
	printf("R of %d G of %d B of %d\n", r, g, b);
	return ((r * 65535) + (g * 256) + b);
}