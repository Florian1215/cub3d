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

double	degre_to_radian(double angle)
{
	return (angle * (PI / 180));
}

t_bool	is_even(int n)
{
	return (n % 2 == 0);
}
