/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sqrt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:15:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/22 19:15:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	sqrt_(double num)
{
	const double	tolerance = 0.000001;
	double			x;
	double			y;

	x = num;
	y = 1;
	if (num <= 0)
		return (-1);
	while (x - y > tolerance)
	{
		x = (x + y) / 2;
		y = num / x;
	}
	return (x);
}
