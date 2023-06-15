/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:27:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/06 20:27:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

static void		set_maps_selection(t_data *data);
static t_ico	get_offset_map(t_map *map);
void			change_n_map(t_data *data, int n);

void	handle_menu(t_data *data)
{
	if (!data->is_menu)
		set_menu(data);
	else
		data->is_menu = FALSE;
}

void	set_menu(t_data *data)
{
	data->is_menu = TRUE;
	draw_square(&data->img, (t_ico){0, 0}, WIN_WIDTH, 0x46458C);
	set_maps_selection(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}

static void	set_maps_selection(t_data *data)
{
	int			i;
	const int	size = MINIMAP_SIZE + MINIMAP_OFFSET;
	t_map		*map;
	t_ico		offset_square;
	t_ico		offset_map;

	i = 0;
	map = data->map;
	while (i < 4)
	{
		offset_square.x = (i % 2) * (MINIMAP_OFFSET * 2 + size);
		offset_square.y = (i > 1) * (MINIMAP_OFFSET * 2 + size);
		draw_square(&data->img, (t_ico){MINIMAP_OFFSET + offset_square.x, \
			MINIMAP_OFFSET + offset_square.y}, size, 0xC2DEDC);
		if (map)
		{
			offset_map = get_offset_map(map);
			offset_map.x += MINIMAP_OFFSET + MINIMAP_OFFSET / 2 + offset_square.x;
			offset_map.y += MINIMAP_OFFSET + MINIMAP_OFFSET / 2 + offset_square.y;
			print_minimap(data, map, offset_map);
			print_player(data, map, offset_map);
			map = map->next;
		}
		i++;
	}
}

static t_ico	get_offset_map(t_map *map)
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

void	select_map(t_data *data, t_ico click)
{
	int			i;
	const int	size = MINIMAP_SIZE + MINIMAP_OFFSET;
	t_map		*map;
	t_ico		offset_square;

	i = 0;
	map = data->map;
	while (i < 4 && map)
	{
		offset_square.x = (i % 2) * (MINIMAP_OFFSET * 2 + size);
		offset_square.y = (i > 1) * (MINIMAP_OFFSET * 2 + size);
		if (click.x >= (MINIMAP_OFFSET + offset_square.x) && \
			click.x <= (MINIMAP_OFFSET + offset_square.x + size) && \
			click.y >= (MINIMAP_OFFSET + offset_square.y) && \
			click.y <= (MINIMAP_OFFSET + offset_square.y + size))
		{
			change_n_map(data, i);
			data->is_menu = FALSE;
			return ;
		}
		map = map->next;
		i++;
	}
}
