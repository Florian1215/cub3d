/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:17:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/22 19:17:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/cub3d.h"

double	distance_between_points(t_dco p1, t_dco p2)
{
	double	x_dist;
	double	y_dist;

	x_dist = p2.x - p1.x;
	y_dist = p2.y - p1.y;
	// printf("\nDIST DEBUG\nx_dist = %f\n", x_dist);
	// printf("p1.x = %f\n", p1.x);
	// printf("p2.x = %f\n", p2.x);
	// printf("p1.y = %f\n", p1.y);
	// printf("p2.y = %f\n", p2.y);
	// printf("y_dist = %f\n", y_dist);
	// printf("distance = %f\n\n", sqrt_(pow_(x_dist, 2) + dpow(y_dist, 2)));
	return (sqrt_(dpow(x_dist, 2) + dpow(y_dist, 2)));
}

double	degre_to_radian(double angle)
{
	return (angle * (3.14159265358979323846 / 180));
}

double	radian_to_degre(double radian)
{
	return (radian * 180 / M_PI);
}

t_bool	is_even(int n)
{
	return (n % 2 == 0);
}
