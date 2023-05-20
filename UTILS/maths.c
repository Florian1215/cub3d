/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:32:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 16:33:39 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

int	abs(int n)
{
	return (n * (-1 * (n < 0) + (n > 0)));
}

double my_sqrt(double num)
{
    double x;
    double y;
	double tolerance = 0.000001;

	x = num;
	y = 1;
    if (num <= 0)
        return -1;
    while (x - y > tolerance)
	{
        x = (x + y) / 2;
        y = num / x;
    }
    return (x);
}

double my_pow(double num, int pow)
{
	double res;

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
	return (my_sqrt(my_pow(p2.x - p1.x, 2) + my_pow(p2.y - p1.y, 2)));
}
