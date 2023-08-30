/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/08/29 13:46:10 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_dco	get_minimap_fov(t_data *data, double angle, t_ico offset);
int				determine_wall_type(t_data *data, t_dco p1);

void	draw_fov(t_data	*data, t_ico offset)
{
	const int	fovs[3] = {70, 90, 110};
	double		angle;
	int			i;
	t_collision	collision;

	i = 0;
	angle = degre_to_radian(data->map->degre - (fovs[data->fov - 4] / 2));
	// printf("angle = %f\n", radian_to_degre(angle - degre_to_radian(data->map->degre)));
	// printf("map angle = %f\n", data->map->degre);
	// printf("adjusted angle = %f\n\n", angle - degre_to_radian(data->map->degre) + degre_to_radian(45));
	while (angle <= degre_to_radian(data->map->degre + (fovs[data->fov - 4] \
		/ 2)) && i < data->distances.size)
	{
		collision = draw_fov_line(data, data->map->pos, get_minimap_fov(data, \
		angle, offset), angle - degre_to_radian(data->map->degre) + degre_to_radian(45), offset);
		data->distances.distance[i] = collision.distance;
		data->distances.face[i] = collision.side;
		data->distances.angle[i] = angle;
		angle += degre_to_radian(DEFINITION);
		i++;
	}
}

static t_dco	get_minimap_fov(t_data *data, double angle, t_ico offset)
{
	t_dco	orientation;

	orientation.x = data->map->pos.x + cos(angle) * FOV_RANGE;
	orientation.y = data->map->pos.y + sin(angle) * FOV_RANGE;
	orientation.x += offset.x + data->map->hhitbox;
	orientation.y += offset.y + data->map->hhitbox;
	return (orientation);
}

double	calculate_distance(t_data *data, t_dco p1, t_dco p2, double angle)
{
	double	distance;

	(void)data;
	// angle += degre_to_radian(45);
	distance = distance_between_points(p1, p2);
	if (radian_to_degre(angle) > 45)
		angle = angle - degre_to_radian(45);
	else
		angle = degre_to_radian(45) - angle;
	distance *= cos(angle);
 	// distance *= cos(degre_to_radian(data->map->degre - \
		// radian_to_degre(atan2(p2.y - p1.y, p2.x - p1.x))));
	return (distance);
}

t_collision	draw_fov_line(t_data *data, t_dco p1, t_dco p2, \
				double angle, t_ico offset)
{
	t_collision		collision;
	t_dco			delta;
	t_dco			initial;
	float			max;
	int				x;
	int				y;

	(void)angle;
	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	initial.x = p1.x;
	initial.y = p1.y;
	max = fmax(fabs(delta.x), fabs(delta.y));
	delta.x /= max;
	delta.y /= max;
	while (((int)(p1.x - p2.x) || (int)(p1.y - p2.y)))
	{
		x = get_map_coordinates(data, p1.x, 0);
		y = get_map_coordinates(data, p1.y, 0);
		if (data->map->m[y][x] == WALL)
		{
			collision.wall = (t_dco){(p1.x), \
				(p1.y)};
			collision.distance = calculate_distance(data, initial, \
				collision.wall, angle);
			collision.side = determine_wall_type(data, p1);
			return (collision);
		}
		else
			mlx_pixel_put_img(&data->img, (int)p1.x + offset.x, (int)p1.y + \
			offset.y, FOV_COLOR);
		p1.x += delta.x;
		p1.y += delta.y;
	}
	collision.distance = 400;
	return (collision);
}
