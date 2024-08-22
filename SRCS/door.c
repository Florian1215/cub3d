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

void	init_door(t_data *data, t_raycatsing *r, t_bool is_open_door)
{
	double	d;

	if (data->door.is_animation && data->door.co.x != r->map_i.x && \
			data->door.co.y != r->map_i.y)
		return ;
	if (is_open_door)
	{
		if (r->wall == WEST || r->wall == EAST)
			d = r->ray.x - r->step.x;
		else
			d = r->ray.y - r->step.y;
		data->door.is_scope = d < 2 && d > data->map->hhitbox;
		r->is_open_door = TRUE;
	}
	else
	{
		data->door.is_scope = r->is_door && r->distance < 2;
		if (!r->is_door)
			return ;
		r->co_door = r->map_i;
	}
	data->door.co = r->map_i;
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
		value = data->map->pos.x + (r->ray.y - r->step.y) * r->direction.x;
	else
	{
		value = data->map->pos.y + (r->ray.x - r->step.x) * r->direction.y;
	}
	value = (1 - (value - (int)value)) * 100;
	if (value > 50)
		return ((100 - data->door.pos) < value);
	return (data->door.pos > value);
}

void	stop_door_animation(t_data *data)
{
	t_case	*c;

	c = &data->map->m[data->door.co.y][data->door.co.x];
	data->door.is_animation = FALSE;
	if (data->door.is_opening)
		*c = DOOR_OPEN;
	else
		*c = DOOR_CLOSE;
}
