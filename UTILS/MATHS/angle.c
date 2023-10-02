/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:34:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/10/02 15:34:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degre_to_radian(double angle)
{
	return (angle * (PI / 180));
}

double	radian_to_degre(double radian)
{
	return (radian * 180 / PI);
}
