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

static void		ray_update(t_data *data, t_ray *ray, t_ico *map_index);
static t_ray	ray_init(t_data *data, t_dco ray_dir);
static void		set_ray_step(t_ray *ray, t_dco ray_dir);

t_ray	ray_cast(t_data *data, t_dco ray_dir)
{
	t_ray	ray;
	t_ico	map_index;

	ray = ray_init(data, ray_dir);
	map_index = (t_ico){(int)data->map->pos.x, (int)data->map->pos.y};
	while (data->map->m[map_index.y][map_index.x] != WALL && data->map->m[map_index.y][map_index.x] != DOOR_CLOSE)
		ray_update(data, &ray, &map_index);
	if (ray.wall == WEST || ray.wall == EAST)
	{
		ray.distance = ray.ray.x - ray.unit_step.x;
		ray.pos.y = data->map->pos.y + ray.distance * ray_dir.y;
	}
	else
	{
		ray.distance = ray.ray.y - ray.unit_step.y;
		ray.pos.x = data->map->pos.x + ray.distance * ray_dir.x;
	}
	if (data->map->m[map_index.y][map_index.x] == DOOR_CLOSE)
		ray.is_door = TRUE;
	return (ray);
}

static void	ray_update(t_data *data, t_ray *ray, t_ico *map_index)
{
	ray->is_door = FALSE;
	if (data->map->m[map_index->y][map_index->x] == DOOR_OPEN)
		ray->is_door = TRUE;
	if (ray->ray.x < ray->ray.y)
	{
		map_index->x += ray->step.x;
		ray->ray.x += ray->unit_step.x;
		if (ray->step.x == 1)
			ray->wall = WEST;
		else
			ray->wall = EAST;
	}
	else
	{
		map_index->y += ray->step.y;
		ray->ray.y += ray->unit_step.y;
		if (ray->step.y == 1)
			ray->wall = NORTH;
		else
			ray->wall = SOUTH;
	}
}

static t_ray	ray_init(t_data *data, t_dco ray_dir)
{
	t_ray	ray;

	ray.pos = data->map->pos;
	ray.unit_step.x = fabs(1 / ray_dir.x);
	ray.unit_step.y = fabs(1 / ray_dir.y);
	ray.ray = (t_dco){0, 0};
	ray.is_door = FALSE;
	set_ray_step(&ray, ray_dir);
	return (ray);
}

static void	set_ray_step(t_ray *ray, t_dco ray_dir)
{
	if (ray_dir.x > 0)
	{
		ray->step.x = 1;
		ray->ray.x = ((int) ray->pos.x + 1 - ray->pos.x) * ray->unit_step.x;
	}
	else
	{
		ray->step.x = -1;
		ray->ray.x = (ray->pos.x - (int) ray->pos.x) * ray->unit_step.x;
	}
	if (ray_dir.y > 0)
	{
		ray->step.y = 1;
		ray->ray.y = ((int) ray->pos.y + 1 - ray->pos.y) * ray->unit_step.y;
	}
	else
	{
		ray->step.y = -1;
		ray->ray.y = (ray->pos.y - (int) ray->pos.y) * ray->unit_step.y;
	}
}