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

t_bool	is_valid_pos(t_map *map, t_dco p1, t_dco p2)
{
	return (map->m[(int)((p1.y + p2.y) / map->square_size)] \
		[(int)((p1.x + p2.x) / map->square_size)] == EMPTY_SPACE);
}
