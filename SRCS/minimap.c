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
	const int	colors[5] = {FLOOR_COLOR, WALL_COLOR, DOOR_CLOSE_COLOR, \
								DOOR_CLOSE_COLOR, DOOR_CLOSE_COLOR};
	t_ico		i;
	t_case		c;

	i.x = 0;
	while (i.x < map->height)
	{
		i.y = 0;
		while (i.y < map->width)
		{
			c = map->m[i.x][i.y];
			if (FLOOR <= c && c <= DOOR_ANIMATION)
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
	double			*value;

	if (!data->launch_animation)
		return ((t_ico){MINIMAP_OFFSET, MINIMAP_OFFSET});
	if (i == 29)
	{
		i = 0;
		data->launch_animation = FALSE;
	}
	offset.x = animation(data->map->omap_menu.x, MINIMAP_OFFSET, i);
	offset.y = animation(data->map->omap_menu.y, MINIMAP_OFFSET, i);
	if (is_look_up(data) || is_look_down(data))
		value = &data->map->pos.y;
	else
		value = &data->map->pos.x;
	if (is_look_up(data) || is_look_left(data))
		*value = animation(ceil(*value), (int)*value + data->map->hhitbox, i);
	else
		*value = animation((int)*value, ceil(*value) - data->map->hhitbox, i);
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
