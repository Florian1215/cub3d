/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordcoordinate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:15:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/25 15:15:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dco	dco_add(t_dco co1, t_dco co2)
{
	return ((t_dco){co1.x + co2.x, co1.y + co2.y});
}

t_dco	dco_mul(t_dco c, double f)
{
	return ((t_dco){c.x * f, c.y * f});
}
