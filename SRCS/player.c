/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:03:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 14:03:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	set_player_position(t_data *data, int k, int i)
{
	data->map[k][i] = EMPTY_SPACE;
	data->player_position.x = (k * data->square_size) + (PLAYER_HITBOX / 4);
	data->player_position.y = (i * data->square_size) + (PLAYER_HITBOX / 4);
	printf("%f - %f\n", data->player_position.x, data->player_position.y);
}

void	print_player(t_data *data)
{
	const t_color	color = {0xD7DF01};

	draw_square(data, data->player_position, PLAYER_HITBOX, color);
}
