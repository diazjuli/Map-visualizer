/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:58:32 by jdiaz             #+#    #+#             */
/*   Updated: 2018/11/09 22:37:52 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		color(void)
{
	float	color;
	float	red;
	float	blue;
	float	green;

	red = 100;
	blue = 100;
	green = 100;
	color = red * 65536 + green * 256 + blue;
	return ((int)color);
}
