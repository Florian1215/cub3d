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

static void		loop_until_hit_wall(t_data *data, t_raycatsing *r, \
					t_raycatsing *d);
t_case			get_case(t_map *map, t_dco p);
t_bool			door_animation(t_data *data, t_raycatsing *r);
void			init_door(t_data *data, t_raycatsing *r, t_raycatsing *door);

void	init_rays(t_raycatsing *r, t_dco pos, int i)
{
	r->is_active = i == WIDTH / 2;
	r->distance = 10000;
	r->is_open_door = FALSE;
	r->is_door = FALSE;
	r->co_door = (t_dco){-1, -1};
	r->pos = pos;
}

void	check_horizontal(t_data *data, t_raycatsing *r, t_raycatsing *door, \
				double angle)
{
	double	a_tan;

	a_tan = -1.0 / tan(angle);
	if (angle > PI)
	{
		r->co.y = (int)r->pos.y - PREC;
		r->co.x = (r->pos.y - r->co.y) * a_tan + r->pos.x;
		r->step = (t_dco){a_tan, -1};
		r->wall = SOUTH;
	}
	else if (angle < PI)
	{
		r->co.y = (int)r->pos.y + 1;
		r->co.x = (r->pos.y - r->co.y) * a_tan + r->pos.x;
		r->step = (t_dco){-a_tan, 1};
		r->wall = NORTH;
	}
	else
	{
		r->co = r->pos;
		r->wall = WEST + (angle != PI);
		return ;
	}
	loop_until_hit_wall(data, r, door);
	r->distance = distance_between_points(r->pos, r->co);
}

void	check_vertical(t_data *data, t_raycatsing *r, t_raycatsing *door, \
				double angle)
{
	double	n_tan;

	n_tan = -tan(angle);
	if (angle > PI2 && angle < PI3)
	{
		r->co.x = (int)r->pos.x - PREC;
		r->co.y = (r->pos.x - r->co.x) * n_tan + r->pos.y;
		r->step = (t_dco){-1, n_tan};
		r->wall = WEST;
	}
	else if (angle < PI2 || angle > PI3)
	{
		r->co.x = (int)r->pos.x + 1;
		r->co.y = (r->pos.x - r->co.x) * n_tan + r->pos.y;
		r->step = (t_dco){1, -n_tan};
		r->wall = EAST;
	}
	else
	{
		r->co = r->pos;
		r->wall = NOTHING + (angle == PI3);
		return ;
	}
	loop_until_hit_wall(data, r, door);
	r->distance = distance_between_points(r->pos, r->co);
}

static void	loop_until_hit_wall(t_data *data, t_raycatsing *r, t_raycatsing *d)
{
	t_case	c;
	int		i;

	i = 0;
	while (i++ < fmax(data->map->height, data->map->width))
	{
		c = get_case(data->map, r->co);
		if (c == DOOR_CLOSE || (c == DOOR_ANIMATION && door_animation(data, r)))
		{
			r->is_door = TRUE;
			d->co_door = r->co;
			break ;
		}
		if (c == WALL)
			break ;
		if (c == DOOR_OPEN || c == DOOR_ANIMATION)
		{
			if (r->is_active)
				init_door(data, r, d);
			d->co_door = r->co;
		}
		r->co = (t_dco){r->co.x + r->step.x, r->co.y + r->step.y};
	}
}
