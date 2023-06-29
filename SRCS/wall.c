/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:37:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/30 01:37:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

static int	check_vertical_wall(t_data *data, t_dco p1);
static int	check_horizontal_wall(t_data *data, t_dco p1);

int	determine_wall_type(t_data *data, t_dco p1)
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;

	x1 = get_map_coordinates(data, p1.x, 0);
	y1 = get_map_coordinates(data, p1.y - NUMBER, 0);
	y2 = get_map_coordinates(data, p1.y + NUMBER, 0);
	if (data->map->m[y1][x1] == WALL && data->map->m[y2][x1] == WALL)
		return (check_vertical_wall(data, p1));
	y1 = get_map_coordinates(data, p1.y, 0);
	x1 = get_map_coordinates(data, p1.x - NUMBER, 0);
	x2 = get_map_coordinates(data, p1.x + NUMBER, 0);
	if (data->map->m[y1][x1] == WALL && data->map->m[y1][x2] == WALL)
		return (check_horizontal_wall(data, p1));
	return (FACE_ERROR);
}

static int	check_vertical_wall(t_data *data, t_dco p1)
{
	int	x1;
	int	x2;
	int	y;

	x1 = get_map_coordinates(data, p1.x - NUMBER, 0);
	x2 = get_map_coordinates(data, p1.x + NUMBER, 0);
	y = get_map_coordinates(data, p1.y, 0);
	if (data->map->m[y][x1] != WALL)
		return (EAST);
	if (data->map->m[y][x2] != WALL)
		return (WEST);
	return (FACE_ERROR);
}

static int	check_horizontal_wall(t_data *data, t_dco p1)
{
	int	x;
	int	y1;
	int	y2;

	x = get_map_coordinates(data, p1.x, 0);
	y1 = get_map_coordinates(data, p1.y - NUMBER, 0);
	y2 = get_map_coordinates(data, p1.y + NUMBER, 0);
	if (data->map->m[y1][x] != WALL)
		return (SOUTH);
	if (data->map->m[y2][x] != WALL)
		return (NORTH);
	return (FACE_ERROR);
}
