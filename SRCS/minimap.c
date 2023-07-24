/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:30:22 by mfinette          #+#    #+#             */
/*   Updated: 2023/05/20 16:10:23 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_minimap(t_data *data, t_map *map, t_ico offset)
{
	const t_color	colors[2] = {{0xFFE79B}, {0xFF0060}};
	int				x;
	int				y;

	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (map->m[x][y] != NOTHING)
				draw_square(&data->img, (t_ico){offset.x + y * map \
				->square_size, offset.y + x * map->square_size}, \
				map->square_size, colors[map->m[x][y]].color);
			y++;
		}
		x++;
	}
}

t_ico	get_minimap_offset(t_data *data)
{
	static int		i = 0;
	t_ico			offset;

	if (i == 29)
	{
		i = 0;
		data->is_launch_animation = FALSE;
	}
	if (!data->is_launch_animation)
		return (data->offset_minimap);
	offset.x = animation(data->map->offset_map_menu.x, \
		data->offset_minimap.x, i);
	offset.y = animation(data->map->offset_map_menu.y, \
		data->offset_minimap.y, i);
	i++;
	return (offset);
}

int	get_map_coordinates(t_data *data, double co, double move)
{
	return ((int)((co + move + data->map->hhitbox) \
		/ data->map->square_size));
}
