/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:12:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/08/05 16:12:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_fov_animation(t_data *data);
static void	set_text_fov(t_data *data);

void	init_fov(t_data *data, int right_pan)
{
	t_menus		i;

	data->fov.s = FOV_90;
	data->fov.prev = FOV_90;
	i = FOV_70;
	while (i <= FOV_110)
	{
		data->menu[i].pos.x = right_pan + (data->size_slider.x * (i - FOV_70)) \
			+ (PADX_MENU * (i - FOV_70)) + 10;
		data->menu[i].pos.y = data->menu[POS_4].pos.y + \
			data->fov.imgs[POS_4].height + 40;
		data->menu[i].size = data->size_slider;
		i++;
	}
	data->menu[FOV_TITLE].pos.x = data->menu[FOV_90].pos.x - 12;
	data->menu[FOV_TITLE].pos.y = data->menu[POS_4].pos.y + 20;
	data->menu[FOV_BG].pos.x = data->menu[FOV_70].pos.x - PADX_MENU;
	data->menu[FOV_BG].pos.y = data->menu[FOV_70].pos.y - PADX_MENU;
	data->menu[FOV_BG].size.x = data->menu[FOV_70].size.x * 3 + PADX_MENU * 4;
	data->menu[FOV_BG].size.y = data->menu[FOV_70].size.y + PADX_MENU * 2;
	data->fov.animation = FALSE;
	data->lvl.is_color = FALSE;
	data->fov.i = 0;
}

void	set_fov_option(t_data *data)
{
	draw_round_rectangle((t_draw){&data->img, BG_ITEM_MENU, MENU_RADIUS + \
		SELECT_RADIUS}, data->menu[FOV_BG].pos, data->menu[FOV_BG].size);
	draw_alpha(&data->img, &data->fov.imgs[3], data->menu[FOV_TITLE].pos);
	if (data->hover >= FOV_70 && data->hover <= FOV_110 \
			&& data->fov.s != data->hover)
		draw_round_rectangle((t_draw){&data->img, FLOOR_COLOR, MENU_RADIUS}, \
			data->menu[data->hover].pos, data->menu[data->hover].size);
	if (!data->fov.animation)
		draw_round_rectangle((t_draw){&data->img, WALL_COLOR, MENU_RADIUS}, \
			data->menu[data->fov.s].pos, data->menu[data->fov.s].size);
	if (data->fov.animation)
		set_fov_animation(data);
	set_text_fov(data);
}

static void	set_fov_animation(t_data *data)
{
	int		*i;
	t_ico	p;

	i = &data->fov.i;
	p.x = animation(data->fov.prev_x, data->menu[data->fov.s].pos.x, *i);
	data->fov.x = p.x;
	p.y = data->menu[FOV_70].pos.y;
	draw_round_rectangle((t_draw){&data->img, WALL_COLOR, MENU_RADIUS}, \
		p, data->menu[FOV_70].size);
	++*i;
	if (*i == 29)
	{
		*i = 0;
		data->fov.animation = FALSE;
	}
}

static void	set_text_fov(t_data *data)
{
	t_menus	i;
	t_img	*f;
	t_ico	p;
	t_ico	s;

	i = FOV_70;
	while (i <= FOV_110)
	{
		p = data->menu[i].pos;
		s = data->menu[i].size;
		f = &data->fov.imgs[i - FOV_70];
		p.x += (s.x / 2) - (f->width / 2);
		p.y += (s.y / 2) - (f->height / 2);
		if (f->img)
			draw_alpha(&data->img, f, p);
		i++;
	}
}
