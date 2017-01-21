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

void	bresenham_retry(t_map *map, int ax, int ay, int az, int bx, int by, int bz)
{
	int		x;
	int		y;
	int		z;
	int		dx;
	int		dy;
	int		dz;
	int		sx;
	int		sy;
	int		sz;
	int		err;
	int		errz;
	int		swap;

	printf("draw line from %i, %i to %i, %i\n", ax, ay, bx, by);
	y = ay;
	x = ax;
	z = az;
	dx = ABS(bx - ax);
	dy = ABS(by - ay);
	dz = ABS(bz - az);
	sx = sign(bx - ax);
	sy = sign(by - ay);
	sz = sign(bz - az);
	err = ABS(dy - dx);
	swap = 0;
	printf("dx is %i, dy is %i, sx is %i, sy is %i\n", dx, dy, sx, sy);
	printf("err is %i\n", err);
	if (dy > dx)
	{
		printf("Y is the driving axis\n");
		swap = 1;
		ft_swap(&dx, &dy);
	}
	else
		printf("X is the driving axis.\n");
	errz = ABS(dz - dx);
	//while ((x * sx <= bx && !swap) || (y * sy <= by && swap))
	while ((swap && y * sy < by) || (!swap && x * sx < bx))
	{
		draw_pixel(map, x, y, z);
		if (err >= 0)
		{
			if (swap)
				x += sx;
			else
		 		y += sy;
			err -= dx;
		}
		if (errz >= 0)
		{
			z += sz;
			errz -= dx;
		}
		if (swap)
			y += sy;
		else
			x += sx;
		err += dy;
		errz += dz;
	}
}

void	draw_bresenham(int ax, int ay, int az, int bx, int by, int bz, t_map *map)
{
	int		x;
	int		y;
	double	z;
	int		dx;
	int		dy;
	int		dz;
	int		error;
	int		swap;
	int		temp;
	int		s1;
	int		s2;
	int		s3;
	int		i;

	printf("draw line from %i, %i, %i to %i, %i, %i\n", ax, ay, az, bx, by, bz);
	x = ax;
	y = ay;
	z = az;
	dx = ABS(bx - ax);
	dy = ABS(by - ay);
	dz = ABS(bz - az);
	s1 = sign(bx - ax);
	s2 = sign(by - ay);
	s3 = sign(bz - az);
	swap = 0;
	if (dy > dx)
	{
		temp = dx;
		dx = dy;
		dy = temp;
		swap = 1;
	}
	error = 2 * dy - dx;
	i = -1;
	while (++i < dx)
	{
		draw_pixel(map, x, y, (double)z);
		while (error >= 0)
		{
			error = error - 2 * dx;
			if (swap)
				x += s1;
			else
				y += s2;
		}
		error = error + 2 * dy;
		if (swap)
			y += s2;
		else
			x += s1;
		z += s3;
	}
}

void	draw_line_v(t_pt *a, t_pt *b, t_map *map)
{
	double	x;
	double	y;
	double	z;
	double	dxdy;
	double	dzdy;

	printf("Drawing a vertical line between %f, %f and %f, %f\n", a->raw_x, a->raw_y, b->raw_x, b->raw_y);
	if (a->y < b->y)
	{
		x = a->view_x;
		y = a->view_y;
		z = a->raw_z;
	}
	else
	{
		x = b->view_x;
		y = b->view_y;
		z = b->raw_z;
	}
	dxdy = (a->view_x - b->view_x) / (a->view_y - b->view_y);
	dzdy = (a->z - b->z) / (a->view_y - b->view_y);
	while (y <= a->view_y || y <= b->view_y)
	{
		draw_pixel(map, (int)round(x), (int)round(y), z);
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

	printf("Drawing a horizontal line between %f, %f and %f, %f\n", a->raw_x, a->raw_y, b->raw_x, b->raw_y);
	if (a->x < b->x)
	{
		x = a->view_x;
		y = a->view_y;
		z = a->raw_z;
	}
	else
	{
		x = b->view_x;
		y = b->view_y;
		z = b->raw_z;
	}
	dydx = (a->view_y - b->view_y) / (a->view_x - b->view_x);
	dzdx = (a->z - b->z) / (a->view_x - b->view_x);
	while (x <= a->view_x || x <= b->view_x)
	{
		draw_pixel(map, (int)round(x), (int)round(y), z);
		y = y + dydx;
		z = z + dzdx;
		x++;
	}
}

/*
** At this point we should check if the line is totally out of range of the image view.
*/

void	draw_line(t_pt *a, t_pt *b, t_map *map)
{
	//printf("Draw line between %f, %f and %f, %f\n", a->view_x, a->view_y, b->view_x, b->view_y);
	if ((a->view_x < 0 && b->view_x < 0) || (a->view_x > map->w && b->view_x > map->w) || (a->view_y < 0 && b->view_y < 0) || (a->view_y > map->h && b->view_y > map->h))
		return ;
	bresenham_retry(map, (int)round(a->view_x), (int)round(a->view_y), a->raw_z, (int)round(b->view_x), (int)round(b->view_y), b->raw_z);
	// if ((ABS((a->view_x) - (b->view_x))) > (ABS((a->view_y) - (b->view_y))))
	// 	//draw_line_h(a, b, map);
	// else
	// 	//draw_line_v(a, b, map);
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
			//printf("Current point is %f, %f, %f\n", map->dots[j][i]->x, map->dots[j][i]->y, map->dots[j][i]->z);
			//printf("Current point is %f, %f, \n", map->dots[j][i]->view_x, map->dots[j][i]->view_y);
			if (map->dots[j][i + 1] != NULL)
				draw_line(map->dots[j][i], map->dots[j][i + 1], map);
			if (map->dots[j + 1] && map->dots[j + 1][i] != NULL)
				draw_line(map->dots[j][i], map->dots[j + 1][i], map);
		}
	}
}
