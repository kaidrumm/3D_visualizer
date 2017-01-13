/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrumm <kdrumm@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 21:14:18 by kdrumm            #+#    #+#             */
/*   Updated: 2016/11/26 21:14:20 by kdrumm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Quick init a single point
*/

t_pt	*new_point(int x, int y, int z)
{
	t_pt	*pt;

	printf("New point at %d, %d, %d\n", x, y, z);
	pt = (t_pt *)malloc(sizeof(t_pt));
	pt->x = x;
	pt->y = y;
	pt->z = z;
	pt->raw_x = x;
	pt->raw_y = y;
	pt->raw_z = z;
	return (pt);
}

void	start_window(t_map *map)
{
	map->w = 800;
	map->h = 600;
	map->cnx = mlx_init();
	map->win = mlx_new_window(map->cnx, map->w, map->h, "FDF");
	map->image_option = 1;
	map->img = mlx_new_image(map->cnx, map->w, map->h);
	map->addr = mlx_get_data_addr(map->img, &(map->bpp), &(map->bpl), &(map->endian));
	printf("Image ptr is %p, Data addr is %p, bits per pixel %i, bytes per line %i, endian %i\n", map->img, map->addr, map->bpp, map->bpl, map->endian);
	center(map);
	helptext(map);
	//project_perspective(map);
	while (1)
	{
		mlx_key_hook(map->win, key_hook, map);
		mlx_mouse_hook(map->win, mouse_hook, map);
		mlx_loop(map->cnx);
	}
}

/*
** Initialize map and the double array of points
*/

void	read_file(int fd, t_map *map)
{
	char	*line;
	char	**numbers;
	int		x;
	int		y;

	y = 0;
	while (get_next_line(fd, &line))
	{
		numbers = ft_strsplit(line, ' ');
		map->dots[y] = (t_pt **)malloc(sizeof(t_pt *) * 2000);
		x = -1;
		while (numbers[++x])
		{
			map->dots[y][x] = new_point(x, y, ft_atoi(numbers[x]));
			if (ft_atoi(numbers[x]) > map->max_z)
				map->max_z = ft_atoi(numbers[x]);
			if (ft_atoi(numbers[x]) < map->min_z)
				map->min_z = ft_atoi(numbers[x]);
		}
		if (x > map->max_x)
			map->max_x = x;
		map->dots[y++][x] = NULL;
	}
	map->max_y = y;
	map->dots[y] = NULL;
}

void	init_map(t_map **map)
{
	(*map) = (t_map *)malloc(sizeof(t_map));
	(*map)->dots = (t_pt ***)malloc(sizeof(t_pt **) * 2000);
	(*map)->max_x = 0;
	(*map)->max_z = 0;
}

/*
** Open file, check params for usage, and call other functions
*/

int		main(int ac, char **av)
{
	int		fd;
	t_map	*map;

	if (ac > 2)
		ft_putendl("Usage: ./fdf filename.fdf");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_putendl("Error");
	init_map(&map);
	read_file(fd, map);
	start_window(map);
	return (1);
}
