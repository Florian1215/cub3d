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

t_dco	get_player_coordinates(t_data *data)
{
	t_dco	co;

	co.x = data->map->pos.x + data->map->hhitbox + MINIMAP_OFFSET;
	co.y = data->map->pos.y + data->map->hhitbox + MINIMAP_OFFSET;
	return (co);
}

void	move_player(t_data *data)
{
	const double	move_speed = data->map->square_size / 10;
	int				x;
	int				y;

	x = get_map_coordinates(data, data->map->pos.x, 0);
	y = get_map_coordinates(data, data->map->pos.y, 0);
	if (data->key_arrow_press[UP] \
			&& data->map->m[get_map_coordinates(data, data->map->pos.y, \
			-move_speed - data->map->qhitbox)][x] == EMPTY_SPACE)
		data->map->pos.y -= move_speed;
	if (data->key_arrow_press[DOWN] \
			&& data->map->m[get_map_coordinates(data, data->map->pos.y, \
			move_speed + data->map->hhitbox)][x] == EMPTY_SPACE)
		data->map->pos.y += move_speed;
	if (data->key_arrow_press[LEFT] \
			&& data->map->m[y][get_map_coordinates(data, data->map->pos.x, \
			move_speed - data->map->hhitbox)] == EMPTY_SPACE)
		data->map->pos.x -= move_speed;
	if (data->key_arrow_press[RIGHT] \
			&& data->map->m[y][get_map_coordinates(data, data->map->pos.x, \
			move_speed + data->map->hhitbox)] == EMPTY_SPACE)
		data->map->pos.x += move_speed;
}

//void	move_player(t_data *data)
//{
//	const double	move_speed = data->map->square_size / 20;
//	t_dco			i;
//
//	if (data->key_arrow_press[UP])
//	{
//		if (data->map->direction < 90)
//		{
//			i.x = cos(degre_to_radian(data->map->direction)) * move_speed;
//			i.y = pow_(move_speed, 2) + dpow(i.x, 2);
//			printf("%f\n%f | %f - %f - %f\n\n", cos(degre_to_radian
//			(data->map->direction)), data->map->direction,
//			move_speed, i.x, i.y);
//			data->map->pos.x += i.x;
//			data->map->pos.y += i.y;
//		}
//		if (data->map->direction < 90 && data->map->direction > 270)
//			data->map->pos.x += move_speed;
//		else
//			data->map->pos.x -= move_speed;
//
//		if (data->map->direction < 90) {
//			printf("90 %f - %f\n", data->map->direction,
//			(data->map->direction * 100 / 90));
//			data->map->pos.y -= move_speed * (data->map->direction
//			* 100 / 90) / 100;
//		}
//		else if (data->map->direction < 180) {
//			printf("180 %f - %f\n", data->map->direction,
//			((180 - data->map->direction) * 100 / 90));
//			data->map->pos.y += move_speed * ((180 -
//			data->map->direction) * 100 / 90) / 100;
//		}

//		if (data->map->direction < 180)
//			data->map->pos.y += move_speed;
//		else
//			data->map->pos.y -= move_speed;
//	}
//	print_minimap(data);
//}

void	rotate_player(t_data *data, int keycode)
{
	if (keycode == A)
		data->map->direction -= 5;
	if (keycode == D)
		data->map->direction += 5;
	if (data->map->direction < 0)
		data->map->direction += 360;
	data->map->direction = fmod(data->map->direction, 360);
}
