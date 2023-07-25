/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:06:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/25 17:06:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_position(t_map *map, int k, int i)
{
	map->m[k][i] = EMPTY_SPACE;
	map->start_pos.x = i;
	map->start_pos.y = k;
	map->pos.x = (i * map->square_size) + map->qhitbox;
	map->pos.y = (k * map->square_size) + map->qhitbox;
}

void	print_player(t_data *data, t_map *map, t_ico offset)
{
	const t_color	color = {0x4C4C6D};

	draw_square(&data->img, (t_ico){offset.x + map->pos.x, \
		offset.y + map->pos.y}, map->hitbox, color.color);
}
