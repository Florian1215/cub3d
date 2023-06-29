/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/29 22:43:16 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	print_fov(t_data	*data)
{
	double		angle;
	int			i;
	t_collision	collision;

	i = 0;
	angle = degre_to_radian(data->map->direction - (FOV / 2));
	while (angle <= degre_to_radian(data->map->direction + (FOV / 2)) && i < data->distances->size)
	{
		collision = draw_fov_line(data, get_player_coordinates(data), \
			get_minimap_fov(data, angle), angle - degre_to_radian(data->map->direction));
		data->distances->distance[i] = collision.distance;
		data->distances->face[i] = collision.side;
		data->distances->angle[i] = angle;
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

double	radian_to_degree(double radian)
{
	return (radian * 180 / M_PI);
}

double	calculate_distance(t_data *data, t_dco p1, t_dco p2)
{
	double	distance;

	distance = distance_between_points(p1, p2);
	distance *= cos(degre_to_radian(data->map->direction - \
		radian_to_degree(atan2(p2.y - p1.y, p2.x - p1.x))));
	return (distance);
}

int	check_vertical_wall(t_data *data, t_dco p1)
{
	int	x1;
	int	x2;
	int	y;

	x1 = get_map_coordinates(data, p1.x - NUMBER, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	x2 = get_map_coordinates(data, p1.x + NUMBER, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	y = get_map_coordinates(data, p1.y, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	if (data->map->m[y][x1] != WALL)
		return (EAST);
	if (data->map->m[y][x2] != WALL)
		return (WEST);
	return (FACE_ERROR);
}

int	check_horizontal_wall(t_data *data, t_dco p1)
{
	int	x;
	int	y1;
	int	y2;
	
	x = get_map_coordinates(data, p1.x, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	y1 = get_map_coordinates(data, p1.y - NUMBER, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	y2 = get_map_coordinates(data, p1.y + NUMBER, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	if (data->map->m[y1][x] != WALL)
		return (SOUTH);
	if (data->map->m[y2][x] != WALL)
		return (NORTH);
	return (FACE_ERROR);
}

int	determine_wall_type(t_data *data, t_dco p1)
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;

	x1 = get_map_coordinates(data, p1.x, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	y1 = get_map_coordinates(data, p1.y - NUMBER, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	y2 = get_map_coordinates(data, p1.y + NUMBER, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	if (data->map->m[y1][x1] == WALL && data->map->m[y2][x1] == WALL)
		return (check_vertical_wall(data, p1));
	y1 = get_map_coordinates(data, p1.y, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	x1 = get_map_coordinates(data, p1.x - NUMBER, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	x2 = get_map_coordinates(data, p1.x + NUMBER, \
		-MINIMAP_OFFSET - data->map->hhitbox);
	if (data->map->m[y1][x1] == WALL && data->map->m[y1][x2] == WALL)
		return (check_horizontal_wall(data, p1));
	return (FACE_ERROR);
}

t_collision	draw_fov_line(t_data *data, t_dco p1, t_dco p2, double angle)
{
	t_collision		collision;
	t_dco			delta;
	t_dco			initial;
	t_dco			vector;
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
			vector = (t_dco){initial.x + delta.x * 20, initial.y + delta.y * 20};
			// collision.distance = distance_between_points(vector, collision.wall);
			collision.distance = calculate_distance(data, initial, collision.wall);
			// collision.distance = calculate_distance(data, initial, collision.wall);
			collision.side = determine_wall_type(data, p1);
			(void)angle;
			printf("player position = %f, %f\n", data->map->pos.x, data->map->pos.y);
			printf("direction = %f\n", data->map->direction);
			return (collision);
		}
		else
			mlx_pixel_put_img(&data->img, (int)p1.x, (int)p1.y, \
			0x5C8984);
		p1.x += delta.x;
		p1.y += delta.y;
	}
	collision.distance = 400;
	return (collision);
}
