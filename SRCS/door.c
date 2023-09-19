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

static t_bool	door_opening(t_data *data, t_raycatsing *r);
static t_bool	door_closing(t_data *data, t_raycatsing *r);
static void		stop_animation(t_data *data);

void	toggle_door(t_data *data)
{
	t_case	*c;

	c = &data->map->m[data->door.co.y][data->door.co.x];
	data->door.is_animation = TRUE;
	data->door.i = 0;
	data->door.is_opening = *c == DOOR_CLOSE;
	*c = DOOR_ANIMATION;
}

t_bool	door_animation(t_data *data, t_raycatsing *r)
{
	if (data->door.is_opening)
		return (door_opening(data, r));
	return (door_closing(data, r));
}

static t_bool	door_opening(t_data *data, t_raycatsing *r)
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
	p = animation(100, 0, data->door.i);
	return (p > value);
}

static t_bool	door_closing(t_data *data, t_raycatsing *r)
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
	p = animation(0, 100, data->door.i);
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
