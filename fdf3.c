/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrumm <kdrumm@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:08:12 by kdrumm            #+#    #+#             */
/*   Updated: 2016/12/14 17:08:13 by kdrumm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Used if projection_option = 1
*/

void	project_isometric(t_map *map)
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
			pt->view_x = (pt->x - pt->y) * map->tile_w;
			pt->view_y = (pt->x + pt->y - pt->z) * map->tile_h;
		}
	}
	//puts("Iso projection done\n");
}

/*
** This function applies prospective projection to the current x,y,z values and
** saves the projection coordinates to view_x and view_y.
** Used if projection_option = 2;
*/

void	project_perspective(t_map *map)
{
	int		i;
	int		j;
	double	f;
	t_pt	*pt;

	f = 420;
	j = -1;
	while (map->dots[++j] != NULL)
	{
		i = -1;
		while (map->dots[j][++i] != NULL)
		{
			pt = map->dots[j][i];
			//printf("Point at %f, %f, %f\n", pt->x, pt->y, pt->z);
			pt->view_x = f * pt->x / (pt->z + 50);
			pt->view_y = f * pt->y / (pt->z + 50);
			//printf("Projected to %f, %f\n", pt->view_x, pt->view_y);
		}
	}
	//puts("Parallel projection done\n");
}

void	rotate_z(t_map *map, double theta)
{
	int		i;
	int		j;
	t_pt	*pt;
	double	temp_x;

	j = -1;
	while (map->dots[++j])
	{
		i = -1;
		while (map->dots[j][++i])
		{
			pt = map->dots[j][i];
			temp_x = (pt->x * cos(theta)) - (pt->y * sin(theta));
			pt->y = (pt->x * sin(theta)) + (pt->y * cos(theta));
			pt->x = temp_x;
		}
	}
}

void	rotate_x(t_map *map, double theta)
{
	int		i;
	int		j;
	t_pt	*pt;
	double	temp_y;

	j = -1;
	while (map->dots[++j])
	{
		i = -1;
		while (map->dots[j][++i])
		{
			pt = map->dots[j][i];
			temp_y = (pt->y * cos(theta)) - (pt->z * sin(theta));
			pt->z = (pt->y * sin(theta)) + (pt->z * cos(theta));
			pt->y = temp_y;
		}
	}
}

void	rotate_y(t_map *map, double theta)
{
	int		i;
	int		j;
	t_pt	*pt;
	double	temp_z;

	j = -1;
	while (map->dots[++j])
	{
		i = -1;
		while (map->dots[j][++i])
		{
			pt = map->dots[j][i];
			temp_z = (pt->z * cos(theta)) - (pt->x * sin(theta));
			pt->x = (pt->z * sin(theta)) + (pt->x * cos(theta));
			pt->z = temp_z;
		}
	}
}
