/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:41:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/30 01:41:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ico	get_minimap_offset_menu(t_map *map);
static t_ico	get_start_minimap_offset_menu(t_map *map, int i);

void	compute_map_offset(t_data *data)
{
	t_map	*map;
	t_menus	i;

	i = POS_1;
	map = data->map;
	while (i < data->n_map && map)
	{
		map->omap_menu = get_minimap_offset_menu(map);
		map->omap_menu.x += MINIMAP_OFFSET / 2 + data->menu[i].pos.x;
		map->omap_menu.y += MINIMAP_OFFSET / 2 + data->menu[i].pos.y;
		map->start_omap = get_start_minimap_offset_menu(map, i);
		map = map->next;
		i++;
	}
}

static t_ico	get_minimap_offset_menu(t_map *map)
{
	int		width;
	int		height;
	t_ico	offset;

	offset = (t_ico){0, 0};
	width = map->width * map->square_size;
	height = map->height * map->square_size;
	if (width > height)
		offset.y = MINIMAP_SIZE / 2 - height / 2;
	else if (height > width)
		offset.x = MINIMAP_SIZE / 2 - width / 2;
	return (offset);
}

static t_ico	get_start_minimap_offset_menu(t_map *map, int i)
{
	if (i == 0)
		return ((t_ico){MINIMAP_OFFSET, MINIMAP_OFFSET});
	else if (i == 1)
		return ((t_ico){map->omap_menu.x, map->omap_menu.y - MINIMAP_SIZE});
	return ((t_ico){map->omap_menu.x, map->omap_menu.y + MINIMAP_SIZE});
}

void	set_minimap_animation(t_data *data)
{
	static int		i = -1;
	t_menus			k;
	t_ico			offset;
	t_map			*map;

	k = -1;
	map = data->map;
	i++;
	while (++k < data->n_map && map)
	{
		offset.x = animation(map->start_omap.x, map->omap_menu.x, i);
		offset.y = animation(map->start_omap.y, map->omap_menu.y, i);
		draw_minimap(data, map, offset);
		draw_player(data, map, offset);
		map = map->next;
	}
	if (i == 28)
	{
		i = -1;
		data->menu_animation = FALSE;
	}
}
