/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:38:57 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/09 22:39:00 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		draw_up(t_fdf *fdf, t_point a, t_point b)
{
	float tmp;
	float diff;

	diff = a.y - b.y;
	if (b.y < a.y)
	{
		tmp = b.y;
		b.y = a.y;
		a.y = tmp;
	}
	while (a.y <= b.y)
	{
		mlx_pixel_put(fdf->mlx, fdf->win, (int)a.x, (int)a.y,
				color());
		a.y++;
	}
	return (1);
}

int		draw_sharp(t_fdf *fdf, t_point a, t_point b, float error)
{
	t_point temp;
	float	m;
	float	inc;

	if (b.y < a.y)
	{
		temp = b;
		b = a;
		a = temp;
	}
	m = (b.x - a.x) / (b.y - a.y);
	inc = m > 0.0 ? 1.0 : -1.0;
	while (++a.y - 1 <= b.y)
	{
		mlx_pixel_put(fdf->mlx, fdf->win, (int)a.x, (int)a.y, color());
		if ((inc == 1.0 && error + m < 0.5) || (inc == -1.0 && error + m > -.5))
			error = error + m;
		else
		{
			a.x = a.x + inc;
			error = error + m - inc;
		}
	}
	return (1);
}

int		draw_line(t_fdf *fdf, t_point a, t_point b)
{
	float slope;
	float error;
	float inc;

	slope = (b.y - a.y) / (b.x - a.x);
	error = 0.0;
	inc = slope > 0.0 ? 1.0 : -1.0;
	if (slope > 1.0 || slope < -1.0)
		return (draw_sharp(fdf, a, b, 0.0));
	while (a.x <= b.x)
	{
		mlx_pixel_put(fdf->mlx, fdf->win, (int)a.x, (int)a.y,
				color());
		if ((inc == 1.0 && error + slope < 0.5) ||
				(inc == -1.0 && error + slope > -.5))
			error = error + slope;
		else
		{
			a.y = a.y + inc;
			error = error + slope - inc;
		}
		a.x++;
	}
	return (1);
}

int		draw_y(t_fdf *fdf, t_map *map)
{
	int		i;
	int		j;

	j = -1;
	while (++j < map->m)
	{
		i = 0;
		while (++i < map->n)
		{
			if (fdf->points[i - 1][j]->x == fdf->points[i][j]->x)
				draw_up(fdf, *(fdf->points[i][j]), *(fdf->points[i - 1][j]));
			else if (fdf->points[i - 1][j]->x < fdf->points[i][j]->x)
				draw_line(fdf, *(fdf->points[i - 1][j]),
						*(fdf->points[i][j]));
			else
				draw_line(fdf, *(fdf->points[i][j]),
						*(fdf->points[i - 1][j]));
		}
	}
	return (1);
}

int		draw_map(t_fdf *fdf, t_map *map)
{
	int		i;
	int		j;

	i = -1;
	while (++i < map->n)
	{
		j = 0;
		while (++j < map->m)
		{
			if (fdf->points[i][j - 1]->x == fdf->points[i][j]->x)
				draw_up(fdf, *(fdf->points[i][j]), *(fdf->points[i][j - 1]));
			else if (fdf->points[i][j - 1]->x < fdf->points[i][j]->x)
				draw_line(fdf, *(fdf->points[i][j - 1]), *(fdf->points[i][j]));
			else
				draw_line(fdf, *(fdf->points[i][j]), *(fdf->points[i][j - 1]));
		}
	}
	return (draw_y(fdf, map));
}
