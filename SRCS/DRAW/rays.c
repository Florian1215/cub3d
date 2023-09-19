/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:18:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/09/10 14:18:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		loop_until_hit_wall(t_data *data, t_raycatsing *r, t_dco pos);
t_case			get_case(t_map *map, t_dco p);
t_bool			door_animation(t_data *data, t_raycatsing *r);

void	check_horizontal(t_data *data, t_raycatsing *r, t_dco pos, \
				double angle)
{
	double	a_tan;

	a_tan = -1.0 / tan(angle);
	if (angle > PI)
	{
		r->co.y = (int)pos.y - PREC;
		r->co.x = (pos.y - r->co.y) * a_tan + pos.x;
		r->step = (t_dco){a_tan, -1};
		r->wall = SOUTH;
	}
	else if (angle < PI)
	{
		r->co.y = (int)pos.y + 1;
		r->co.x = (pos.y - r->co.y) * a_tan + pos.x;
		r->step = (t_dco){-a_tan, 1};
		r->wall = NORTH;
	}
	else
	{
		r->co = pos;
		r->wall = WEST + (angle != PI);
		return ;
	}
	loop_until_hit_wall(data, r, pos);
	r->distance = distance_between_points(pos, r->co);
}

void	check_vertical(t_data *data, t_raycatsing *r, t_dco pos, \
				double angle)
{
	double	n_tan;

	n_tan = -tan(angle);
	if (angle > PI2 && angle < PI3)
	{
		r->co.x = (int)pos.x - PREC;
		r->co.y = (pos.x - r->co.x) * n_tan + pos.y;
		r->step = (t_dco){-1, n_tan};
		r->wall = WEST;
	}
	else if (angle < PI2 || angle > PI3)
	{
		r->co.x = (int)pos.x + 1;
		r->co.y = (pos.x - r->co.x) * n_tan + pos.y;
		r->step = (t_dco){1, -n_tan};
		r->wall = EAST;
	}
	else
	{
		r->co = pos;
		r->wall = NOTHING + (angle == PI3);
		return ;
	}
	loop_until_hit_wall(data, r, pos);
	r->distance = distance_between_points(pos, r->co);
}

static void	loop_until_hit_wall(t_data *data, t_raycatsing *r, t_dco pos)
{
	t_case	c;
	int		i;

	i = 0;
	r->is_open_door = FALSE;
	while (i++ < fmax(data->map->height, data->map->width))
	{
		c = get_case(data->map, r->co);
		if (c == DOOR_CLOSE || (c == DOOR_ANIMATION && door_animation(data, r)))
		{
			r->wall = DOOR;
			break ;
		}
		if (c == WALL)
			break ;
		if (c == DOOR_OPEN && r->is_active && !data->door.is_animation)
		{
			data->door.is_scope = distance_between_points(pos, r->co) < 2 \
				&& distance_between_points(pos, r->co) > data->map->hhitbox;
			data->door.co = (t_ico){r->co.x, r->co.y};
			data->door.is_opening = TRUE;
			r->is_open_door = TRUE;
		}
		r->co = (t_dco){r->co.x + r->step.x, r->co.y + r->step.y};
	}
}
