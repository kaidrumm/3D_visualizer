/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrumm <kdrumm@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:24:08 by kdrumm            #+#    #+#             */
/*   Updated: 2016/12/14 17:24:09 by kdrumm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Called by print_dots. Transforms the view coordinates to be centered on the
** image window.
*/

void	center_screen(t_map *map)
{
	int		i;
	int		j;
	t_pt	*pt;

	j = -1;
	while (map->dots[++j] != NULL)
	{
		i = -1;
		while (map->dots[j][++i] != NULL)
		{
			pt = map->dots[j][i];
			pt->view_x = pt->view_x + (map->w / 2);
			pt->view_y = pt->view_y + (map->h / 2);
		}
	}
}

/*
** Moves the actual coordinates of the object to be centered on the origin.
*/

void	center(t_map *map)
{
	int		i;
	int		j;
	t_pt	*pt;

	j = -1;
	while (map->dots[++j] != NULL)
	{
		i = -1;
		while (map->dots[j][++i] != NULL)
		{
			pt = map->dots[j][i];
			pt->x = pt->x - (map->max_x / 2);
			pt->y = pt->y - (map->max_y / 2);
			pt->z = pt->z - ((map->max_z + map->min_z) / 2);
			pt->color = set_color(map, pt->z);
		}
	}
}

/*
** Scales the height of the object's z axis, can be used to flip
*/

void	scale(t_map *map, double o)
{
	int		i;
	int		j;
	t_pt	*pt;

	j = -1;
	while (map->dots[++j] != NULL)
	{
		i = -1;
		while (map->dots[j][++i] != NULL)
		{
			pt = map->dots[j][i];
			pt->z = pt->z * o;
		}
	}
}

/*
** Perspective and isometric zooms should be handled differently.
*/

void	zoom_control(t_map *map, double o)
{
	if (map->projection_option == 1)
		zoom(map, o);
	else
		map->z_dist /= o;
	if (map->z_dist < (map->max_z - map->min_z))
		map->z_dist = 42 * (map->max_z - map->min_z);
}

/*
** Applies a multiplier to the object's x and y dimensions
*/

void	zoom(t_map *map, double o)
{
	int		i;
	int		j;
	t_pt	*pt;

	j = -1;
	while (map->dots[++j] != NULL)
	{
		i = -1;
		while (map->dots[j][++i] != NULL)
		{
			pt = map->dots[j][i];
			pt->x = pt->x * o;
			pt->y = pt->y * o;
		}
	}
}
