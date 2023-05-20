/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:32:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 18:16:48 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

int	abs_(int n)
{
	return (n * (-1 * (n < 0) + (n > 0)));
}

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

double	pow_(double num, int pow)
{
	double	res;

	res = 1;
	while (pow > 0)
	{
		res *= num;
		pow--;
	}
	return (res);
}

double	distance_between_points(t_co p1, t_co p2)
{
	return (sqrt_(pow_(p2.x - p1.x, 2) + pow_(p2.y - p1.y, 2)));
}
