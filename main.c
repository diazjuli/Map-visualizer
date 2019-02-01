/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 23:20:30 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/13 12:50:55 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_array(char **to_free, int m)
{
	int i;

	i = 0;
	while (i < m)
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	free_all(t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->map->n)
	{
		j = 0;
		while (j < fdf->map->m)
		{
			free(fdf->points[i][j]);
			j++;
		}
		free(fdf->points[i]);
		free(fdf->map->alt[i]);
		i++;
	}
	free(fdf->points);
	free(fdf->map->alt);
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(0);
}

int		check_map(char *str, t_map *map)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		if (map->m == -1)
			map->m = ft_num_words(line);
		else if (map->m != ft_num_words(line))
			return (-1);
		map->n++;
		free(line);
		free_array(split, map->m);
	}
	close(fd);
	map->alt = (int **)(malloc(sizeof(int *) * map->n));
	if (!(map->alt))
		return (-1);
	return (1);
}

int		init(t_fdf *fdf, t_map *map, char *str)
{
	fdf->name = str;
	map->n = 0;
	map->m = -1;
	fdf->z_mult = 10.0;
	fdf->zoom = 0;
	fdf->mouse_press = 0;
	fdf->mouse_x = 0;
	fdf->mouse_y = 0;
	fdf->z_rot = 0.0;
	fdf->y_rot = 0.0;
	fdf->x_rot = 0.0;
	if (check_map(str, map) == -1)
		return (-1);
	fdf->points = (t_point ***)malloc(sizeof(t_point *) * map->n);
	if (!fdf->points)
		return (-1);
	fdf->x_trans = 0;
	fdf->y_trans = 0;
	return (1);
}

int		main(int argc, char **argv)
{
	t_fdf fdf;
	t_map map;

	if (argc != 2)
		return (0);
	if (init(&fdf, &map, argv[1]) == -1)
		return (-1);
	if (read_coords(0, &fdf, &map) == -1)
		return (-1);
	if ((fdf.mlx = mlx_init()) == NULL)
		return (-1);
	if ((fdf.win = mlx_new_window(fdf.mlx, XDIM, YDIM, fdf.name)) == NULL)
		return (-1);
	z_rotate(&fdf, &map, -.6);
	x_rotate(&fdf, &map, .7);
	apply_translation(&fdf, &map, XMID, YMID);
	draw_map(&fdf, &map);
	mlx_hook(fdf.win, 4, 0, hook_mouse_press, &fdf);
	mlx_hook(fdf.win, 5, 0, hook_mouse_release, &fdf);
	mlx_hook(fdf.win, 6, 0, hook_mouse_move, &fdf);
	mlx_hook(fdf.win, 17, 0, hook_close, &fdf);
	mlx_hook(fdf.win, 2, 0, key_press, &fdf);
	mlx_loop(fdf.mlx);
	return (1);
}
