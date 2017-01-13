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
			printf("X = %f adjusted to %f\n", pt->x, pt->x - (map->max_x / 2));
			pt->x = pt->x - (map->max_x / 2);
			printf("Y = %f adjusted to %f\n", pt->y, pt->y - (map->max_y / 2));
			pt->y = pt->y - (map->max_y / 2);
			printf("Z = %f adjusted to %f\n", pt->z, pt->z - ((map->max_z + map->min_z) / 2));
			pt->z = pt->z - ((map->max_z + map->min_z) / 2);
			pt->color = set_color(map, pt->z);
			printf("Color is %06x\n", pt->color);
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
	center(map);
}
