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

void	print_minimap(t_data *data, t_map *map, t_ico offset, t_bool background)
{
	const int	colors[4] = {FLOOR_COLOR, WALL_COLOR, DOOR_OPEN_COLOR, \
								DOOR_CLOSE_COLOR};
	t_ico		i;
	t_case		c;

	i.x = 0;
	while (i.x < map->height)
	{
		i.y = 0;
		while (i.y < map->width)
		{
			c = map->m[i.x][i.y];
			if (((c == FLOOR || c == DOOR_OPEN) && background) || \
				(!background && (c == WALL || c == DOOR_CLOSE)))
			{
				draw_square((t_draw){&data->img, colors[map->m[i.x][i.y]], \
				0}, (t_ico){offset.x + i.y * map->square_size, offset.y + \
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
	offset.x = animation(data->map->omap_menu.x, MINIMAP_OFFSET, i);
	offset.y = animation(data->map->omap_menu.y, MINIMAP_OFFSET, i);
	i++;
	return (offset);
}

t_dco	get_map_dco(t_map *map, t_ico offset)
{
	t_dco			pos;

	pos.x = offset.x + (map->pos.x * map->square_size);
	pos.y = offset.y + (map->pos.y * map->square_size);
	return (pos);
}

t_ico	get_map_ico(t_map *map, t_ico offset)
{
	t_ico			pos;

	pos.x = offset.x + (map->pos.x - map->hhitbox) * map->square_size;
	pos.y = offset.y + (map->pos.y - map->hhitbox) * map->square_size;
	return (pos);
}
