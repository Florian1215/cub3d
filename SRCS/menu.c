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

#include "cub3d.h"

void			compute_map_offset(t_data *data);
static void		draw_rounded_squares(t_data *data);
static void		set_minimap(t_data *data);
void			set_minimap_animation(t_data *data);

void	handle_menu(t_data *data)
{
	if (!data->in_menu)
	{
		compute_map_offset(data);
		data->menu_animation = TRUE;
	}
	else
	{
		data->launch_animation = TRUE;
		data->in_menu = FALSE;
	}
}

void	set_menu(t_data *data)
{
	data->in_menu = TRUE;
	draw_rectangle(&data->img, (t_ico){0, 0}, \
		(t_ico){WIN_WIDTH - 1, WIN_HEIGHT - 1}, BG_MENU);
	draw_rounded_squares(data);
	if (data->menu_animation)
		set_minimap_animation(data);
	else
		set_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->logo, \
		data->menu[LOGO].pos.x, data->menu[LOGO].pos.y);
	if (data->hover_animation)
		data->hover_animation = FALSE;
}

static void	draw_rounded_squares(t_data *data)
{
	const t_color	colors[2] = {{BG_MAP_MENU}, {BG_MAP_MENU_HOVER}};
	t_pos			i;

	i = POS_1;
	while (i < 4)
	{
		draw_round_square(&data->img, data->menu[i].pos, data->menu[i].size.x, \
			20, colors[i == data->hover].color);
		i++;
	}
}

static void	set_minimap(t_data *data)
{
	t_pos	i;
	t_map	*map;

	compute_map_offset(data);
	i = POS_1;
	map = data->map;
	while (i < 4 && map)
	{
		print_minimap(data, map, map->offset_map_menu);
		print_player(data, map, map->offset_map_menu);
		map = map->next;
		i++;
	}
}

t_pos	select_map(t_data *data, t_ico click)
{
	t_map	*map;
	t_pos	i;

	i = POS_1;
	map = data->map;
	while (i < 4 && map)
	{
		if (click.x >= data->menu[i].pos.x && \
			click.x <= data->menu[i].pos.x + data->menu[i].size.x && \
			click.y >= data->menu[i].pos.y && \
			click.y <= data->menu[i].pos.y + data->menu[i].size.y)
			return (i);
		map = map->next;
		i++;
	}
	return (POS_ERROR);
}
