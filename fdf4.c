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

void	helptext(t_map *map)
{
	mlx_string_put(map->cnx, map->win, 10, 10, 0xf4ce42, "Welcome to FDF by KaiDrumm!");
	mlx_string_put(map->cnx, map->win, 10, 30, 0xf4ce42, "Press H to return to helptext at any time.");
	mlx_string_put(map->cnx, map->win, 10, 50, 0xf4ce42, "Spacebar will reset the image to its initial view.");
	mlx_string_put(map->cnx, map->win, 10, 70, 0xf4ce42, "Press ESC to exit (but you know you don't want to)");
	mlx_string_put(map->cnx, map->win, 10, 90, 0xf4ce42, "Plus and minus will zoom in and out");
	mlx_string_put(map->cnx, map->win, 10, 110, 0xf4ce42, "* and / will scale the Z axis for you,");
	mlx_string_put(map->cnx, map->win, 10, 130, 0xf4ce42, "And = will flip the Z axis entirely.");
	mlx_string_put(map->cnx, map->win, 10, 150, 0xf4ce42, "Numpad keys make it shift side to side or rotate.");
	mlx_string_put(map->cnx, map->win, 10, 170, 0xf4ce42, "Enter will toggle between image setting vs pixel setting.");
	mlx_string_put(map->cnx, map->win, 10, 190, 0xf4ce42, "On the number row, press 1 for isometric projection, or 2 for parallel.");
	mlx_string_put(map->cnx, map->win, 10, 350, 0xf442a1, "Press any key to begin.");
	// mlx_string_put(map->cnx, map->win, 10, 210, 0xf4ce42, "Welcome to FDF!");
	// mlx_string_put(map->cnx, map->win, 10, 230, 0xf4ce42, "Welcome to FDF!");
	// mlx_string_put(map->cnx, map->win, 10, 250, 0xf4ce42, "Welcome to FDF!");
	// mlx_string_put(map->cnx, map->win, 10, 270, 0xf4ce42, "Welcome to FDF!");
	// mlx_string_put(map->cnx, map->win, 10, 290, 0xf4ce42, "Welcome to FDF!");
	// mlx_string_put(map->cnx, map->win, 10, 310, 0xf4ce42, "Welcome to FDF!");
	// mlx_string_put(map->cnx, map->win, 10, 330, 0xf4ce42, "Welcome to FDF!");
	// mlx_string_put(map->cnx, map->win, 10, 350, 0xf4ce42, "Welcome to FDF!");
	//expose_hook(map);
}

/*
** Not currently used
*/

int		mouse_hook(int button, int x, int y, t_map *map)
{
	t_map *cpy;

	cpy = map;
	printf("Mouse says: %d (%d, %d)\n", button, x, y);
	return (0);
}

/*
** Image_option exists to demonstrate the speed improvements made by building an image
** locally and then sending it to the window, versus sending one pixel at a time.
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
	printf("Keycode is %d\n", keycode);
	if (keycode == 18) // numrow 1
		map->projection_option = 1;
	if (keycode == 19) // numrow 2
		map->projection_option = 2;
	expose_hook(map);
	return (1);
}

int		key_hook(int keycode, t_map *map)
{
	if (keycode == 53) // ESC
		exit(0);
	if (keycode == 76) // numpad enter
		map->image_option *= -1;
	if (keycode == 49) // Spacebar
		reset(map);
	if (keycode == 69) // plus
		zoom(map, 1.5);
	if (keycode == 78) // minus
		zoom(map, .75);
	if (keycode == 81)
		scale(map, -1);
	if (keycode == 67) // asterisk
		scale(map, 1.5);
	if (keycode == 75) // forward slash
		scale(map, .75);
	if (keycode == 89) // numpad 7
		rotate_x(map, 0.1);
	if (keycode == 91) // numpad 8
		rotate_x(map, -0.1);
	if (keycode == 86) // numpad 4
		rotate_y(map, 0.1);
	if (keycode == 87) // numpad 5
		rotate_y(map, -0.1);
	if (keycode == 83) // numpad 1
		rotate_z(map, 0.1);
	if (keycode == 84) // numpad 2
		rotate_z(map, -0.1);
	return (key_hook2(keycode, map));
}
