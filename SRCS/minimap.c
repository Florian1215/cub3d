/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:30:22 by mfinette          #+#    #+#             */
/*   Updated: 2023/05/20 16:10:23 by mfinette         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_minimap(t_data *data, t_map *map, t_ico offset)
{
	const t_color	colors[2] = {{FLOOR_COLOR}, {WALL_COLOR}};
	t_ico			i;

	i.x = 0;
	while (i.x < map->height)
	{
		i.y = 0;
		while (i.y < map->width)
		{
			if (map->m[i.x][i.y] != NOTHING)
			{
				draw_square((t_draw){&data->img, colors[map->m[i.x][i.y]].color \
				, 0}, (t_ico){offset.x + i.y * map->square_size, offset.y + \
				i.x * map->square_size}, map->square_size);
			}
			i.y++;
		}
		i.x++;
	}
}

t_ico	get_minimap_offset(t_data *data)
{
	static int		i = 0;
	t_ico			offset;

	if (i == 29)
	{
		i = 0;
		data->launch_animation = FALSE;
	}
	if (i == 0)
		data->start_animation = get_timestamp();
	sleep_until(i * FRAME + data->start_animation);
	if (!data->launch_animation)
		return ((t_ico){MINIMAP_OFFSET, MINIMAP_OFFSET});
	offset.x = animation(data->map->offset_map_menu.x, \
		MINIMAP_OFFSET, i);
	offset.y = animation(data->map->offset_map_menu.y, \
		MINIMAP_OFFSET, i);
	i++;
	return (offset);
}

int	get_map_coordinates(t_data *data, double co, double move)
{
	return ((int)((co + move + data->map->hhitbox) \
		/ data->map->square_size));
}
