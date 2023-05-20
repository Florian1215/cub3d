/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:03:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 21:07:08 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	set_player_position(t_data *data, int k, int i)
{
	data->map[k][i] = EMPTY_SPACE;
	data->player_position.x = (i * data->square_size) + (PLAYER_HITBOX / 4);
	data->player_position.y = (k * data->square_size) + (PLAYER_HITBOX / 4);
	printf("%f - %d\n", data->square_size, k);
}

void	print_player(t_data *data)
{
	const t_color	color = {0xD7DF01};

	draw_square(data, data->player_position, PLAYER_HITBOX, color);
	print_fov(data);
}

void	print_fov(t_data	*data)
{
	double	angle;

	angle = angle_to_radian(data->player_direction - (FOV / 2));
	while (angle <= angle_to_radian(data->player_direction + (FOV / 2)))
	{
		draw_line(data, get_player_coordinates(data), get_minimap_fov(data, angle));
		angle += angle_to_radian(0.1);
	}	
}

t_co	get_player_coordinates(t_data *data)
{
	t_co	co;

	co.x = data->player_position.x + (PLAYER_HITBOX / 2) + MINIMAP_OFFSET;
	co.y = data->player_position.y + (PLAYER_HITBOX / 2) + MINIMAP_OFFSET;
	return (co);
}
void	move_player(t_data *data)
{
	const double	move_speed = 0.2;

	if (data->key_arrow_press[UP])
		data->player_position.y -= move_speed;
	if (data->key_arrow_press[DOWN])
		data->player_position.y += move_speed;
	if (data->key_arrow_press[LEFT])
		data->player_position.x -= move_speed;
	if (data->key_arrow_press[RIGHT])
		data->player_position.x += move_speed;
	print_minimap(data);
}

void	rotate_player(int keycode, t_data *data)
{
	data->player_direction = fmod(data->player_direction, 360);
	if (keycode == A)
	{
		data->player_direction -= 5;
	}
	if (keycode == D)
	{
		data->player_direction += 5;
	}
	print_minimap(data);
}

double	angle_to_radian(double angle)
{
	return (angle * (3.14159265358979323846 / 180));
}

t_co	get_minimap_fov(t_data *data, double angle)
{
	t_co	orientation;

	orientation.x = data->player_position.x + cos(angle) * 60;
	orientation.y = data->player_position.y + sin(angle) * 60;
	orientation.x += MINIMAP_OFFSET + (PLAYER_HITBOX / 2);
	orientation.y += MINIMAP_OFFSET + (PLAYER_HITBOX / 2);
	return (orientation);
}
