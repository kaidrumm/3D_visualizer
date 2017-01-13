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

	//printf("Drawing a pixel at %i, %i with image_option %i\n", x, y, map->image_option);
	color = set_color(map, z);
	//printf("color as a number is %x, or as a char is %s\n", color, color);
	if (map->image_option == 1)
	{
		//printf("memory address at %i\n", ((map->bpp) * x / 8) + ((map->bpl) * y));
		addr = &(map->addr[((map->bpp) * x / 8) + ((map->bpl) * y)]);
		ft_memcpy(addr, &color, (map->bpp) / 8);
	}
	else 
		mlx_pixel_put(map->cnx, map->win, x, y, 0Xd56497);
}

void	draw_line_v(t_pt *a, t_pt *b, t_map *map)
{
	double	x;
	double	y;
	double	z;
	double	dxdy;
	double	dzdy;

	if (a->y < b->y)
	{
		x = a->view_x;
		y = a->view_y;
		z = a->z;
	}
	else
	{
		x = b->view_x;
		y = b->view_y;
		z = b->z;
	}
	dxdy = (a->view_x - b->view_x) / (a->view_y - b->view_y);
	dzdy = (a->z - b->z) / (a->view_y - b->view_y);
	while (y <= a->view_y || y <= b->view_y)
	{
		draw_pixel(map, (int)round(x), (int)round(y), (int)round(z));
		x = x + dxdy;
		z = z + dzdy;
		y++;
	}
}

void	draw_line_h(t_pt *a, t_pt *b, t_map *map)
{
	double	x;
	double	y;
	double	z;
	double	dydx;
	double	dzdx;

	if (a->x < b->x)
	{
		x = a->view_x;
		y = a->view_y;
		z = a->z;
	}
	else
	{
		x = b->view_x;
		y = b->view_y;
		z = b->z;
	}
	dydx = (a->view_y - b->view_y) / (a->view_x - b->view_x);
	dzdx = (a->z - b->z) / (a->view_x - b->view_x);
	while (x <= a->view_x || x <= b->view_x)
	{
		draw_pixel(map, (int)round(x), (int)round(y), (int)round(z));
		y = y + dydx;
		z = z + dzdx;
		x++;
	}
}

void	draw_line(t_pt *a, t_pt *b, t_map *map)
{
	//printf("Draw line between %f, %f and %f, %f\n", a->view_x, a->view_y, b->view_x, b->view_y);
	if ((ABS((a->view_x) - (b->view_x))) > (ABS((a->view_y) - (b->view_y))))
		draw_line_h(a, b, map);
	else
		draw_line_v(a, b, map);
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
			printf("Current point is %f, %f, %f\n", map->dots[j][i]->x, map->dots[j][i]->y, map->dots[j][i]->z);
			printf("Current point is %f, %f, \n", map->dots[j][i]->view_x, map->dots[j][i]->view_y);
			if (map->dots[j][i + 1] != NULL)
				draw_line(map->dots[j][i], map->dots[j][i + 1], map);
			if (map->dots[j + 1] && map->dots[j + 1][i] != NULL)
				draw_line(map->dots[j][i], map->dots[j + 1][i], map);
		}
	}
}
