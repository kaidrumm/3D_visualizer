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

int		set_color(t_map *map, int z)
{
	int		r;
	int		g;
	int		b;
	double	scale;

	r = 42;
	g = 242;
	b = 42;
	scale = (map->max_z + map->min_z) / 2;
	if (z < 0)
	{
		r -= (int)round(z * 200 / scale);
		b -= (int)round(z * 200 / scale);
	}
	if (z > 0)
	{
		r += (int)round(z * 200 / scale);
		b += (int)round(z * 200 / scale);
	}
	return ((r * 65535) + (b * 256) + g);
}