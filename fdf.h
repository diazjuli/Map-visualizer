/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 23:12:09 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/13 12:51:06 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define KEY_ESC	53
# define KEY_UP		126
# define KEY_LEFT   123
# define KEY_DOWN	125
# define KEY_RIGHT  124

# define XDIM		1000
# define YDIM		750
# define XMID		XDIM / 2
# define YMID		YDIM / 2

# define LEN(N)		(YDIM / (N) / 2)
# define MAP_MID_X	map->m / 2
# define MAP_MID_Y	map->n / 2

# include "./libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "./minilibx_macos/mlx.h"

typedef struct	s_map
{
	int		**alt;
	int		n;
	int		m;
}				t_map;

typedef struct	s_point
{
	float	x;
	float	y;
	float	z;
	int		z_or;
}				t_point;

typedef struct	s_fdf
{
	char	*name;
	t_point	***points;
	t_map	*map;
	float	z_mult;
	int		zoom;
	float	x_rot;
	float	y_rot;
	float	z_rot;
	int		x_trans;
	int		y_trans;
	void	*mlx;
	void	*win;
	int		mouse_press;
	int		mouse_x;
	int		mouse_y;
}				t_fdf;

int				read_coords(int fd, t_fdf *fdf, t_map *map);
int				draw_map(t_fdf *fdf, t_map *map);
int				reset_points(t_fdf *fdf, t_map *map);
int				apply_translation(t_fdf *fdf, t_map *map, int x, int y);
int				z_rotate(t_fdf *fdf, t_map *map, float angle);
int				x_rotate(t_fdf *fdf, t_map *map, float angle);
int				y_rotate(t_fdf *fdf, t_map *map, float angle);
int				hook_mouse_release(int button, int x, int y, t_fdf *fdf);
int				hook_mouse_press(int button, int x, int y, t_fdf *fdf);
int				hook_mouse_move(int x, int y, t_fdf *fdf);
int				key_press(int keycode, t_fdf *fdf);
int				color(void);
void			free_all(t_fdf *fdf);
void			free_array(char **to_free, int m);
int				hook_close(void *fdf);

#endif
