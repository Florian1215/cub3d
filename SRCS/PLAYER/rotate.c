/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:06:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/25 17:06:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_direction(t_map *map)
{
	map->radian = degre_to_radian(map->degre);
	map->direction.x = cos(map->radian);
	map->direction.y = sin(map->radian);
}

void	rotate_player(t_data *data)
{
	if (data->key_arrow_press[KP_I] || data->key_arrow_press[KP_O])
	{
		if (data->key_arrow_press[KP_I])
			data->map->degre -= PLAYER_ROTATE;
		if (data->key_arrow_press[KP_O])
			data->map->degre += PLAYER_ROTATE;
		if (data->map->degre < 0)
			data->map->degre += 360;
		data->map->degre = fmod(data->map->degre, 360);
		update_direction(data->map);
	}
}
