/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 14:50:23 by jdiaz             #+#    #+#             */
/*   Updated: 2018/10/25 20:44:29 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		y_rotate(t_fdf *fdf, t_map *map, float angle)
{
	float	x;
	float	z;
	int		i;
	int		j;

	i = -1;
	while (++i < map->n)
	{
		j = -1;
		while (++j < map->m)
		{
			x = fdf->points[i][j]->x;
			z = fdf->points[i][j]->z;
			fdf->points[i][j]->x = x * cos(angle) - z * sin(angle);
			fdf->points[i][j]->z = x * sin(angle) + z * cos(angle);
		}
	}
	fdf->y_rot += angle;
	return (1);
}

int		x_rotate(t_fdf *fdf, t_map *map, float angle)
{
	float	y;
	float	z;
	int		i;
	int		j;

	i = -1;
	while (++i < map->n)
	{
		j = -1;
		while (++j < map->m)
		{
			y = fdf->points[i][j]->y;
			z = fdf->points[i][j]->z;
			fdf->points[i][j]->y = y * cos(angle) - z * sin(angle);
			fdf->points[i][j]->z = y * sin(angle) + z * cos(angle);
		}
	}
	fdf->x_rot += angle;
	return (1);
}

int		z_rotate(t_fdf *fdf, t_map *map, float angle)
{
	float	x;
	float	y;
	int		i;
	int		j;

	i = -1;
	while (++i < map->n)
	{
		j = -1;
		while (++j < map->m)
		{
			x = fdf->points[i][j]->x;
			y = fdf->points[i][j]->y;
			fdf->points[i][j]->x = x * cos(angle) - y * sin(angle);
			fdf->points[i][j]->y = x * sin(angle) + y * cos(angle);
		}
	}
	fdf->z_rot += angle;
	return (1);
}

int		apply_translation(t_fdf *fdf, t_map *map, int x, int y)
{
	int i;
	int j;

	i = -1;
	while (++i < map->n)
	{
		j = -1;
		while (++j < map->m)
		{
			fdf->points[i][j]->x += (float)x;
			fdf->points[i][j]->y += (float)y;
		}
	}
	fdf->x_trans += x;
	fdf->y_trans += y;
	return (1);
}
