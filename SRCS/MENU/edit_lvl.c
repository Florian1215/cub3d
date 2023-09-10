/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_lvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:29:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/08/14 16:29:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_edit_animation(t_data *data);
int			get_gradient(t_color c1, t_color c2, int i);
static void	set_text_lvl(t_data *data);

void	init_lvl(t_data *data)
{
	t_menus		i;

	data->lvl.s = LVL_NORMAL;
	data->lvl.prev = LVL_NORMAL;
	i = LVL_EASY;
	while (i <= LVL_HARD)
	{
		data->menu[i].pos = data->menu[i - 3].pos;
		data->menu[i].pos.y += PADY_LVL;
		data->menu[i].size = data->size_slider;
		i++;
	}
	data->menu[LVL_TITLE].pos = data->menu[FOV_TITLE].pos;
	data->menu[LVL_TITLE].pos.x -= PADX_LVL;
	data->menu[LVL_TITLE].pos.y += PADY_LVL;
	data->menu[LVL_BG].pos.x = data->menu[LVL_EASY].pos.x - PADX_MENU;
	data->menu[LVL_BG].pos.y = data->menu[LVL_EASY].pos.y - PADX_MENU;
	data->menu[LVL_BG].size.x = data->menu[LVL_EASY].size.x * 3 + PADX_MENU * 4;
	data->menu[LVL_BG].size.y = data->menu[LVL_EASY].size.y + PADX_MENU * 2;
	data->lvl.animation = FALSE;
	data->lvl.is_color = TRUE;
	data->lvl.colors[0] = (t_color){EASY_COLOR};
	data->lvl.colors[1] = (t_color){NORMAL_COLOR};
	data->lvl.colors[2] = (t_color){HARD_COLOR};
	data->lvl.i = 0;
}

void	set_lvl_option(t_data *data)
{
	if (data->lvl.animation)
		data->lvl.c = get_gradient(data->lvl.prev_color, \
				data->lvl.colors[data->lvl.s - LVL_EASY], data->lvl.i);
	else
		data->lvl.c = data->lvl.colors[data->lvl.s - LVL_EASY].color;
	draw_round_rectangle((t_draw){&data->img, data->lvl.c, MENU_RADIUS + \
		SELECT_RADIUS}, data->menu[LVL_BG].pos, data->menu[LVL_BG].size);
	draw_alpha(&data->img, &data->lvl.imgs[3], data->menu[LVL_TITLE].pos);
	if (data->hover >= LVL_EASY && data->hover <= LVL_HARD \
			&& data->lvl.s != data->hover)
		draw_round_rectangle((t_draw){&data->img, FLOOR_COLOR, MENU_RADIUS}, \
			data->menu[data->hover].pos, data->menu[data->hover].size);
	if (data->lvl.animation)
		set_edit_animation(data);
	else
		draw_round_rectangle((t_draw){&data->img, WALL_COLOR, MENU_RADIUS}, \
	data->menu[data->lvl.s].pos, data->menu[data->lvl.s].size);
	set_text_lvl(data);
}

static void	set_edit_animation(t_data *data)
{
	int		*i;
	t_ico	p;

	i = &data->lvl.i;
	p.x = animation(data->lvl.prev_x, data->menu[data->lvl.s].pos.x, *i);
	data->lvl.x = p.x;
	p.y = data->menu[LVL_EASY].pos.y;
	draw_round_rectangle((t_draw){&data->img, WALL_COLOR, MENU_RADIUS}, \
		p, data->menu[LVL_EASY].size);
	++*i;
	if (*i == 29)
	{
		*i = 0;
		data->lvl.animation = FALSE;
	}
}

static void	set_text_lvl(t_data *data)
{
	t_menus	i;
	t_img	*f;
	t_ico	p;
	t_ico	s;

	i = LVL_EASY;
	while (i <= LVL_HARD)
	{
		p = data->menu[i].pos;
		s = data->menu[i].size;
		f = &data->lvl.imgs[i - LVL_EASY];
		p.x += (s.x / 2) - (f->width / 2);
		p.y += (s.y / 2) - (f->height / 2) + i - 4;
		if (f->img)
			draw_alpha(&data->img, f, p);
		i++;
	}
}
