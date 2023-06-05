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

void	print_fov(t_data	*data)
{
	double	angle;

	angle = degre_to_radian(data->map->direction - (FOV / 2));
	while (angle <= degre_to_radian(data->map->direction + (FOV / 2)))
	{
		draw_fov_line(data, get_player_coordinates(data), \
			get_minimap_fov(data, angle));
		angle += degre_to_radian(0.1);
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

t_collision	draw_fov_line(t_data *data, t_dco p1, t_dco p2)
{
	t_collision		collision;
	t_dco			delta;
	float			max;
	int				x;
	int				y;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
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
			collision.wall = (t_dco){(p1.x / data->map->square_size), \
				(p1.y / data->map->square_size)};
			collision.distance = distance_between_points(p1, collision.wall);
			return (collision);
		}
		else
			mlx_pixel_put_img(&data->img, (int)p1.x, (int)p1.y, \
			0x30888888);
		p1.x += delta.x;
		p1.y += delta.y;
	}
	collision.distance = distance_between_points(p1, p2);
	return (collision);
}
