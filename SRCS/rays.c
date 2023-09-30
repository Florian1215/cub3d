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

static void	init_step(t_raycatsing *r);
t_case		get_case(t_map *map, t_ico p);
static void	ray_update(t_raycatsing *ray);
t_bool		door_animation(t_data *data, t_raycatsing *r);
void		init_door(t_data *data, t_raycatsing *r, t_bool is_open_door);

void	init_raycasting(t_data *data, t_raycatsing *r, t_dco ray_dir, int i)
{
	r->pos = data->map->pos;
	r->step.x = fabs(1 / ray_dir.x);
	r->step.y = fabs(1 / ray_dir.y);
	r->direction = ray_dir;
	r->is_active = i == WIDTH / 2;
	r->ray = (t_dco){0, 0};
	r->is_door = FALSE;
	r->is_open_door = FALSE;
	r->co_door = (t_ico){-1, -1};
	r->map_i = (t_ico){(int)data->map->pos.x, (int)data->map->pos.y};
	init_step(r);
}

static void	init_step(t_raycatsing *r)
{
	if (r->direction.x > 0)
	{
		r->map_step.x = 1;
		r->ray.x = ((int)r->pos.x + 1 - r->pos.x) * r->step.x;
	}
	else
	{
		r->map_step.x = -1;
		r->ray.x = (r->pos.x - (int)r->pos.x) * r->step.x;
	}
	if (r->direction.y > 0)
	{
		r->map_step.y = 1;
		r->ray.y = ((int)r->pos.y + 1 - r->pos.y) * r->step.y;
	}
	else
	{
		r->map_step.y = -1;
		r->ray.y = (r->pos.y - (int)r->pos.y) * r->step.y;
	}
}

void	loop_until_hit_wall(t_data *data, t_raycatsing *r)
{
	t_case	c;

	while (TRUE)
	{
		c = get_case(data->map, r->map_i);
		if (c == DOOR_CLOSE || (c == DOOR_ANIMATION && door_animation(data, r)))
		{
			r->is_door = TRUE;
			r->co_door = r->map_i;
			break ;
		}
		if (c == WALL)
			break ;
		if (c == DOOR_OPEN || c == DOOR_ANIMATION)
		{
			if (r->is_active)
				init_door(data, r, TRUE);
			r->co_door = r->map_i;
		}
		ray_update(r);
	}
	set_co_ray(data, r);
}

static void	ray_update(t_raycatsing *r)
{
	if (r->ray.x < r->ray.y)
	{
		r->map_i.x += r->map_step.x;
		r->ray.x += r->step.x;
		r->wall = EAST - (r->map_step.x == 1);
	}
	else
	{
		r->map_i.y += r->map_step.y;
		r->ray.y += r->step.y;
		r->wall = SOUTH - (r->map_step.y == 1);
	}
}

void	set_co_ray(t_data *data, t_raycatsing *r)
{
	if (r->wall == WEST || r->wall == EAST)
	{
		r->distance = r->ray.x - r->step.x;
		r->pos.y = data->map->pos.y + r->distance * r->direction.y;
	}
	else
	{
		r->distance = r->ray.y - r->step.y;
		r->pos.x = data->map->pos.x + r->distance * r->direction.x;
	}
	r->co = (t_dco){data->map->pos.x + r->distance * r->direction.x, \
		data->map->pos.y + r->distance * r->direction.y};
}
