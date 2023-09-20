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

void	init_door(t_data *data, t_raycatsing *r, double d, t_bool opening)
{
	if (opening)
		data->door.is_scope = d < 2 && d > data->map->hhitbox;
	else
		data->door.is_scope = r->is_door && d < 2;
	data->door.co = (t_ico){r->co.x, r->co.y};
	data->door.is_opening = opening;
}

void	toggle_door(t_data *data)
{
	t_case	*c;

	c = &data->map->m[data->door.co.y][data->door.co.x];
	data->door.is_animation = TRUE;
	data->door.i = 0;
	data->door.is_opening = *c == DOOR_CLOSE;
	*c = DOOR_ANIMATION;
	data->door.is_scope = FALSE;
}

t_bool	door_animation(t_data *data, t_raycatsing *r)
{
	double	p;
	double	value;

	if (data->door.i == 28)
		return (stop_animation(data), TRUE);
	if (r->wall == SOUTH || r->wall == NORTH)
		value = r->co.x - (int)r->co.x;
	else
		value = r->co.y - (int)r->co.y;
	value *= 100;
	p = animation(100 * data->door.is_opening, 100 * \
		(!data->door.is_opening), data->door.i);
	return (p > value);
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
