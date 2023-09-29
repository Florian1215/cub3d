/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:22:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/09/18 22:22:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_door(t_data *data, t_raycatsing *r, t_raycatsing *door)
{
	double	d;

	if (data->door.is_animation && (data->door.co.x != (int)r->pos.x || \
			data->door.co.y != (int)r->pos.y))
		return ;
	if (door)
	{
		d = distance_between_points(r->co, r->pos);
		data->door.is_scope = d < 2 && d > data->map->hhitbox;
		door->is_open_door = TRUE;
	}
	else
	{
		data->door.is_scope = r->is_door && r->distance < 2;
		r->co_door = r->pos;
	}
	data->door.co = (t_ico){r->pos.x, r->pos.y};
}

void	toggle_door(t_data *data)
{
	t_case	*c;
	t_bool	is_opening;
	int		start;

	c = &data->map->m[data->door.co.y][data->door.co.x];
	if (data->door.is_animation)
	{
		is_opening = !data->door.is_opening;
		start = data->door.pos;
	}
	else
	{
		start = 50;
		is_opening = *c == DOOR_CLOSE;
		*c = DOOR_ANIMATION;
	}
	data->door.i = 0;
	data->door.is_opening = is_opening;
	data->door.start = start * (is_opening || \
		(!is_opening && data->door.is_animation));
	data->door.end = 50 * (!is_opening);
	data->door.is_animation = TRUE;
}

t_bool	door_animation(t_data *data, t_raycatsing *r)
{
	double	value;

	if (r->wall == SOUTH || r->wall == NORTH)
		value = r->pos.x - (int)r->pos.x;
	else
		value = r->pos.y - (int)r->pos.y;
	value *= 100;
	if (value > 50)
		return ((100 - data->door.pos) < value);
	return (data->door.pos > value);
}

void	stop_animation(t_data *data)
{
	t_case	*c;

	c = &data->map->m[data->door.co.y][data->door.co.x];
	data->door.is_animation = FALSE;
	if (data->door.is_opening)
		*c = DOOR_OPEN;
	else
		*c = DOOR_CLOSE;
}
