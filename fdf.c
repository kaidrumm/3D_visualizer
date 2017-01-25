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

	pt = (t_pt *)malloc(sizeof(t_pt));
	pt->x = x;
	pt->y = y;
	pt->z = z;
	pt->raw_x = x;
	pt->raw_y = y;
	pt->raw_z = z;
	return (pt);
}

/*
** Just a helper function to make read_file short enough for norm
*/

void	z_limits(t_map *map, int x)
{
	if (x > map->max_z)
		map->max_z = x;
	if (x < map->min_z)
		map->min_z = x;
}

/*
** Initialize map and the double array of points
*/

int		read_file(int fd, t_map *map)
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
		MALLOC_GUARD(map->dots[y]);
		x = -1;
		while (numbers[++x])
		{
			map->dots[y][x] = new_point(x, y, ft_atoi(numbers[x]));
			z_limits(map, ft_atoi(numbers[x]));
		}
		if (x > map->max_x)
			map->max_x = x;
		map->dots[y++][x] = NULL;
	}
	map->max_y = y;
	map->dots[y] = NULL;
	return (1);
}

int		init_map(t_map **map)
{
	(*map) = (t_map *)malloc(sizeof(t_map));
	MALLOC_GUARD(*map);
	(*map)->dots = (t_pt ***)malloc(sizeof(t_pt **) * 2000);
	MALLOC_GUARD((*map)->dots);
	(*map)->max_x = 0;
	(*map)->max_z = 0;
	(*map)->w = 800;
	(*map)->h = 600;
	(*map)->cnx = mlx_init();
	(*map)->win = mlx_new_window((*map)->cnx, (*map)->w, (*map)->h, "FDF");
	(*map)->image_option = 1;
	(*map)->projection_option = 1;
	(*map)->img = mlx_new_image((*map)->cnx, (*map)->w, (*map)->h);
	(*map)->addr = mlx_get_data_addr((*map)->img, &((*map)->bpp),
		&((*map)->bpl), &((*map)->endian));
	if (!(*map)->addr || !(*map)->img || !(*map)->win)
		return (0);
	return (1);
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
	if (fd == -1 || !init_map(&map) || !read_file(fd, map))
	{
		ft_putendl("Invalid map or out of memory");
		return (0);
	}
	display(map);
	return (1);
}
