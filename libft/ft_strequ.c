/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 19:45:09 by jdiaz             #+#    #+#             */
/*   Updated: 2018/10/19 20:41:45 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	if (!s1)
		return (-1);
	if (!s2)
		return (2);
	if (ft_strcmp(s1, s2) == 0)
		return (1);
	else
		return (0);
}
