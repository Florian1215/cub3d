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

static void		stop_animation(t_data *data);

void	init_door(t_data *data, t_raycatsing *r, t_raycatsing *door)
{
	double	d;

	if (data->door.is_animation && (data->door.co.x != (int)r->co.x || \
			data->door.co.y != (int)r->co.y))
		return ;
	if (door)
	{
		d = distance_between_points(r->pos, r->co);
		data->door.is_scope = d < 2 && d > data->map->hhitbox;
		door->is_open_door = TRUE;
	}
	else
	{
		data->door.is_scope = r->is_door && r->distance < 2;
		r->co_door = r->co;
	}
	data->door.co = (t_ico){r->co.x, r->co.y};
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
		start = 100 - data->door.pos;
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

	if (data->door.i == 28)
		return (stop_animation(data), TRUE);
	if (r->wall == SOUTH || r->wall == NORTH)
		value = r->co.x - (int)r->co.x;
	else
		value = r->co.y - (int)r->co.y;
	value *= 100;
	data->door.pos = animation(data->door.start, data->door.end, data->door.i);
	if (value > 50)
	{
		data->door.pos = 100 - data->door.pos;
		return (data->door.pos < value);
	}
	return (data->door.pos > value);
}

static void	stop_animation(t_data *data)
{
	t_case	*c;

	c = &data->map->m[data->door.co.y][data->door.co.x];
	data->door.is_animation = FALSE;
	if (data->door.is_opening)
		*c = DOOR_OPEN;
	else
		*c = DOOR_CLOSE;
}
