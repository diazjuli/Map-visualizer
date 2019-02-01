/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:19:17 by jdiaz             #+#    #+#             */
/*   Updated: 2018/10/25 20:30:49 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		reset_points(t_fdf *fdf, t_map *map)
{
	int		y;
	int		x;

	y = 0;
	fdf->x_trans = 0;
	fdf->y_trans = 0;
	fdf->x_rot = 0;
	fdf->y_rot = 0;
	fdf->z_rot = 0;
	while (y < map->n)
	{
		x = 0;
		while (x < map->m)
		{
			fdf->points[y][x]->z = (float)(map->alt[y][x] * fdf->z_mult);
			fdf->points[y][x]->x = (float)((x - MAP_MID_X) * LEN(map->n));
			fdf->points[y][x]->y = (float)((y - MAP_MID_Y) * LEN(map->n));
			x++;
		}
		y++;
	}
	return (1);
}

int		make_points(t_fdf *fdf, t_map *map)
{
	int		y;
	int		x;
	t_point	*point;

	y = -1;
	while (++y < map->n)
	{
		x = -1;
		fdf->points[y] = (t_point **)malloc(sizeof(t_point *) * map->m);
		if (!fdf->points[y])
			return (-1);
		while (++x < map->m)
		{
			if ((point = (t_point *)malloc(sizeof(t_point))) == NULL)
				return (-1);
			point->z = (float)(map->alt[y][x] * fdf->z_mult);
			point->x = (float)((x - MAP_MID_X) * LEN(map->n));
			point->y = (float)((y - MAP_MID_Y) * LEN(map->n));
			point->z_or = point->z;
			fdf->points[y][x] = point;
		}
	}
	fdf->map = map;
	return (1);
}

int		read_coords(int fd, t_fdf *fdf, t_map *map)
{
	char	*line;
	char	**split;
	int		row;
	int		i;

	row = 0;
	fd = open(fdf->name, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd, &line) != 0)
	{
		i = -1;
		split = ft_strsplit(line, ' ');
		map->alt[row] = (int *)malloc(sizeof(int) * map->m);
		if (!map->alt[row] || (map->m != ft_num_words(line)))
			return (-1);
		while (++i < map->m)
			map->alt[row][i] = ft_atoi(split[i]);
		row++;
		free(line);
		free_array(split, map->m);
	}
	close(fd);
	return (make_points(fdf, map));
}
