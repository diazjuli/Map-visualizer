/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 21:53:41 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/13 12:49:31 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		zoom(t_fdf *fdf, int keycode)
{
	float	zoom_in;
	int		i;
	int		j;
	float	x_temp;
	float	y_temp;

	zoom_in = keycode == 34 ? 1.1 : 0.9;
	x_temp = fdf->x_trans;
	y_temp = fdf->y_trans;
	i = -1;
	apply_translation(fdf, fdf->map, -fdf->x_trans, -fdf->y_trans);
	while (++i < fdf->map->n)
	{
		j = -1;
		while (++j < fdf->map->m)
		{
			fdf->points[i][j]->x *= zoom_in;
			fdf->points[i][j]->y *= zoom_in;
			fdf->points[i][j]->z *= zoom_in;
		}
	}
	apply_translation(fdf, fdf->map, x_temp, y_temp);
	return (1);
}

int		key_press(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		free_all(fdf);
	mlx_clear_window(fdf->mlx, fdf->win);
	if (keycode == 69 || keycode == 78)
	{
		fdf->z_mult += keycode == 69 ? 4 : -4;
		reset_points(fdf, fdf->map);
		z_rotate(fdf, fdf->map, -.6);
		x_rotate(fdf, fdf->map, .7);
		apply_translation(fdf, fdf->map, XMID, YMID);
	}
	if (keycode == KEY_LEFT)
		apply_translation(fdf, fdf->map, XDIM / 50, 0);
	if (keycode == KEY_RIGHT)
		apply_translation(fdf, fdf->map, -XDIM / 50, 0);
	if (keycode == KEY_DOWN)
		apply_translation(fdf, fdf->map, 0, YDIM / 50);
	if (keycode == KEY_UP)
		apply_translation(fdf, fdf->map, 0, -YDIM / 50);
	if (keycode == 34 || keycode == 31)
		zoom(fdf, keycode);
	return (draw_map(fdf, fdf->map));
}

int		hook_mouse_move(int x, int y, t_fdf *fdf)
{
	int		x_temp;
	int		y_temp;

	x_temp = fdf->x_trans;
	y_temp = fdf->y_trans;
	if (fdf->mouse_press == 1)
	{
		mlx_clear_window(fdf->mlx, fdf->win);
		apply_translation(fdf, fdf->map, -fdf->x_trans, -fdf->y_trans);
		y_rotate(fdf, fdf->map, (float)(fdf->mouse_x - x) / 100.0);
		x_rotate(fdf, fdf->map, (float)(fdf->mouse_y - y) / 100.0);
		fdf->mouse_x = x;
		fdf->mouse_y = y;
		apply_translation(fdf, fdf->map, x_temp, y_temp);
		draw_map(fdf, fdf->map);
	}
	return (1);
}

int		hook_mouse_release(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)
	{
		fdf->mouse_press = 0;
	}
	x = y;
	return (0);
}

int		hook_mouse_press(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)
	{
		fdf->mouse_press = 1;
		fdf->mouse_x = x;
		fdf->mouse_y = y;
	}
	return (1);
}
