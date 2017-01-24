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