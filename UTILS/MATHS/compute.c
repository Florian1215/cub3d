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

#include "cub3d.h"

double	vector_length(t_dco i)
{
	return (sqrt_(i.x * i.x + i.y * i.y));
}

double	distance_between_points(t_dco p1, t_dco p2)
{
	double	x_dist;
	double	y_dist;

	x_dist = p2.x - p1.x;
	y_dist = p2.y - p1.y;
	return (sqrt_(dpow(x_dist, 2) + dpow(y_dist, 2)));
}

t_bool	point_belongs_to_line(t_dco p1, t_dco p2, t_dco p)
{
	double	r;

	r = (p2.y - p1.y) * (p.x - p1.x) + ((p2.x * -1) + p1.x) * (p.y - p1.y);
	return (r > -0.01 && r < 0.01);
}

t_bool	is_even(int n)
{
	return (n % 2 == 0);
}
