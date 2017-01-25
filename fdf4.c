/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrumm <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:11:14 by kdrumm            #+#    #+#             */
/*   Updated: 2016/12/14 17:11:15 by kdrumm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Not currently used
*/

int		mouse_hook(void)
{
	return (0);
}

/*
** Image_option exists to demonstrate the speed improvements made by building
** an image locally and then sending it to the window, versus sending one
** pixel at a time.
*/

int		expose_hook(t_map *map)
{
	if (map->image_option == 1)
		ft_bzero(map->addr, map->bpl * map->h);
	mlx_clear_window(map->cnx, map->win);
	if (map->projection_option == 1)
		project_isometric(map);
	if (map->projection_option == 2)
		project_perspective(map);
	print_dots(map);
	if (map->image_option == 1)
		mlx_put_image_to_window(map->cnx, map->win, map->img, 0, 0);
	return (1);
}

int		key_hook2(int keycode, t_map *map)
{
	if (keycode == 49)
		reset(map);
	if (keycode == 76)
		map->image_option *= -1;
	if (keycode == 18)
		map->projection_option = 1;
	if (keycode == 19)
		map->projection_option = 2;
	if (keycode == 4)
		return (helptext(map, 0xf4ce42, mlx_string_put));
	expose_hook(map);
	return (1);
}

int		key_hook(int keycode, t_map *map)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 69)
		zoom_control(map, 1.5);
	if (keycode == 78)
		zoom_control(map, .75);
	if (keycode == 81)
		scale(map, -1);
	if (keycode == 67)
		scale(map, 1.5);
	if (keycode == 75)
		scale(map, .75);
	if (keycode == 89)
		rotate_x(map, 0.1);
	if (keycode == 91)
		rotate_x(map, -0.1);
	if (keycode == 86)
		rotate_y(map, 0.1);
	if (keycode == 87)
		rotate_y(map, -0.1);
	if (keycode == 83)
		rotate_z(map, 0.1);
	if (keycode == 84)
		rotate_z(map, -0.1);
	return (key_hook2(keycode, map));
}

void	display(t_map *map)
{
	map->tile_w = map->w / (map->max_x * 2);
	map->tile_h = map->h / (map->max_y * 2);
	map->z_dist = 4 * (map->max_z - map->min_z);
	map->z_dist = (map->max_z - map->min_z);
	center(map);
	helptext(map, 0xf4ce42, mlx_string_put);
	while (1)
	{
		mlx_key_hook(map->win, key_hook, map);
		mlx_mouse_hook(map->win, mouse_hook, map);
		mlx_loop(map->cnx);
	}
}
