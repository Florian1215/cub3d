/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:03:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/22 13:44:07 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	set_player_position(t_data *data, int k, int i)
{
	data->map[k][i] = EMPTY_SPACE;
	data->player.pos.x = (i * data->square_size) + data->player.qhitbox;
	data->player.pos.y = (k * data->square_size) + data->player.qhitbox;
}

void	print_player(t_data *data)
{
	const t_color	color = {0xD7DF01};

	print_fov(data);
	draw_square(data, data->player.pos, data->player.hitbox, color);
}

t_dco	get_player_coordinates(t_data *data)
{
	t_dco	co;

	co.x = data->player.pos.x + data->player.hhitbox + MINIMAP_OFFSET;
	co.y = data->player.pos.y + data->player.hhitbox + MINIMAP_OFFSET;
	return (co);
}

void	move_player(t_data *data)
{
	int				x;
	int				y;
	const double	move_speed = (double)MINIMAP_SIZE / 600;

	x = get_map_coordinates(data, data->player.pos.x, 0);
	y = get_map_coordinates(data, data->player.pos.y, 0);
	if (data->key_arrow_press[UP] \
			&& data->map[get_map_coordinates(data, data->player.pos.y, \
			-move_speed - data->player.hhitbox)][x] == EMPTY_SPACE)
		data->player.pos.y -= move_speed;
	if (data->key_arrow_press[DOWN] \
			&& data->map[get_map_coordinates(data, data->player.pos.y, \
			move_speed + data->player.hhitbox)][x] == EMPTY_SPACE)
		data->player.pos.y += move_speed;
	if (data->key_arrow_press[LEFT] \
			&& data->map[y][get_map_coordinates(data, data->player.pos.x, \
			-move_speed - data->player.hhitbox)] == EMPTY_SPACE)
		data->player.pos.x -= move_speed;
	if (data->key_arrow_press[RIGHT] \
			&& data->map[y][get_map_coordinates(data, data->player.pos.x, \
			move_speed + data->player.hhitbox)] == EMPTY_SPACE)
		data->player.pos.x += move_speed;
	print_minimap(data);
}

void	rotate_player(t_data *data, int keycode)
{
	data->player.direction = fmod(data->player.direction, 360);
	if (keycode == A)
		data->player.direction -= 5;
	if (keycode == D)
		data->player.direction += 5;
	print_minimap(data);
}
