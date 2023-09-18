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
void			set_fov_option(t_data *data);
void			set_lvl_option(t_data *data);
void			set_minimap_animation(t_data *data);
static void		set_minimap(t_data *data);

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
	pthread_t		t[MAX_THREAD];

	data->in_menu = TRUE;
	draw_rectangle((t_draw){&data->img, BG_MENU, 0}, (t_ico){0, 0}, \
		(t_ico){WIDTH - 1, HEIGHT - 1});
	pthread_create(t, NULL, (void *)draw_rounded_squares, data);
	pthread_create(t + 1, NULL, (void *)set_fov_option, data);
	pthread_create(t + 2, NULL, (void *)set_lvl_option, data);
	pthread_join(t[0], NULL);
	if (data->menu_animation)
		set_minimap_animation(data);
	else
		set_minimap(data);
	pthread_join(t[1], NULL);
	pthread_join(t[2], NULL);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	if (data->logo.img)
		draw_alpha(&data->img, &data->logo, data->menu[LOGO].pos, RLOGO);
	if (data->hover_animation)
		data->hover_animation = FALSE;
}

static void	draw_rounded_squares(t_data *data)
{
	const t_color	colors[2] = {{BG_ITEM_MENU}, {BG_ITEM_MENU_HOVER}};
	t_menus			i;

	i = POS_1;
	while (i < data->n_map)
	{
		draw_round_square((t_draw){&data->img, colors[i == data->hover].color, \
			20}, data->menu[i].pos, data->menu[i].size.x);
		i++;
	}
}

static void	set_minimap(t_data *data)
{
	t_menus	i;
	t_map	*map;

	compute_map_offset(data);
	i = POS_1;
	map = data->map;
	while (i < data->n_map && map)
	{
		print_minimap(data, map, map->omap_menu, TRUE);
		print_minimap(data, map, map->omap_menu, FALSE);
		print_player(data, map, map->omap_menu);
		map = map->next;
		i++;
	}
}

t_menus	select_binds(t_data *data, t_ico click)
{
	t_menus	i;

	i = POS_1;
	while (i <= LVL_HARD)
	{
		if (click.x >= data->menu[i].pos.x && \
			click.x <= data->menu[i].pos.x + data->menu[i].size.x && \
			click.y >= data->menu[i].pos.y && \
			click.y <= data->menu[i].pos.y + data->menu[i].size.y)
			return (i);
		i++;
	}
	return (POS_ERROR);
}
