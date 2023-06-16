/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/22 22:23:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	draw_fov(t_data	*data)
{
	double		angle;
	int			i;
	t_collision	collision;

	i = 0;
	angle = degre_to_radian(data->map->direction - (FOV / 2));
	while (angle <= degre_to_radian(data->map->direction + (FOV / 2)) && i < data->distances->size)
	{
		collision = draw_fov_line(data, get_player_coordinates(data), \
			get_minimap_fov(data, angle));
		data->distances->distance[i] = collision.distance;
		angle += degre_to_radian(DEFINITION);
		i++;
	}
}

t_dco	get_minimap_fov(t_data *data, double angle)
{
	t_dco	orientation;

	orientation.x = data->map->pos.x + cos(angle) * FOV_RANGE;
	orientation.y = data->map->pos.y + sin(angle) * FOV_RANGE;
	orientation.x += MINIMAP_OFFSET + data->map->hhitbox;
	orientation.y += MINIMAP_OFFSET + data->map->hhitbox;
	return (orientation);
}

t_bool	point_belongs_to_line(t_dco p1, t_dco p2, t_dco p3)
{
	if (p1.x <= p2.x && p1.x <= p3.x && p1.y <= p2.y && p1.y <= p3.y)
		return (TRUE);
	if (p1.x >= p2.x && p1.x >= p3.x && p1.y >= p2.y && p1.y >= p3.y)
		return (TRUE);
	return (FALSE);
}

t_collision	draw_fov_line(t_data *data, t_dco p1, t_dco p2)
{
	t_collision		collision;
	t_dco			delta;
	t_dco			initial;
//	t_dco			vector;
	float			max;
	int				x;
	int				y;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	initial.x = p1.x;
	initial.y = p1.y;
	max = fmax(fabs(delta.x), fabs(delta.y));
	delta.x /= max;
	delta.y /= max;
	while (((int)(p1.x - p2.x) || (int)(p1.y - p2.y)))
	{
		x = get_map_coordinates(data, p1.x, \
			-MINIMAP_OFFSET - data->map->hhitbox);
		y = get_map_coordinates(data, p1.y, \
			-MINIMAP_OFFSET - data->map->hhitbox);
		if (data->map->m[y][x] == WALL)
		{
			collision.wall = (t_dco){(p1.x), \
				(p1.y)};
//			vector = (t_dco){initial.x + delta.x * 20, initial.y + delta.y * 20};
			// if (!point_belongs_to_line(collision.wall, initial, vector))
				collision.distance = distance_between_points(initial, collision.wall);
			// else
			// 	collision.distance = 3;
			// printf("initial = %f, %f\n", initial.x, initial.y);
			// printf("collision point = %f, %f\n", collision.wall.x, collision.wall.y);
			// printf("distance = %f\n", collision.distance);
			// printf("vector = %f, %f\n\n", vector.x, vector.y);
//			printf("player position = %f, %f\n", data->minimap->pos.x, data->minimap->pos.y);
//			printf("direction = %f\n", data->minimap->direction);
			return (collision);
		}
		else
			mlx_pixel_put_img(&data->img, (int)p1.x, (int)p1.y, \
			0x5C8984);
		p1.x += delta.x;
		p1.y += delta.y;
	}
	collision.distance = distance_between_points(p1, p2);
	return (collision);
}
