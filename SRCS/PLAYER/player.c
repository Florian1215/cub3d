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

void	set_player_position(t_map *map, int y, int x)
{
	map->m[y][x] = FLOOR;
	map->start_pos.x = x;
	map->start_pos.y = y;
	map->pos.x = x + 0.5;
	map->pos.y = y + 0.5;
}

void	draw_player(t_data *data, t_map *map, t_ico offset)
{
	const t_color	color = {PLAYER_COLOR};

	draw_square((t_draw){&data->img, color.color, 0}, \
		get_map_ico(map, offset), map->hitbox);
}
