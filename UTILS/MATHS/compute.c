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
	return (sqrt_(pow_(p2.x - p1.x, 2) + pow_(p2.y - p1.y, 2)));
}

double	degre_to_radian(double angle)
{
	return (angle * (3.14159265358979323846 / 180));
}
