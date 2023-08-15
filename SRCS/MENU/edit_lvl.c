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

static void	set_edit_animation(t_data *data, int *i);
int			get_gradient(t_color c1, t_color c2, int i);
static void	set_text_lvl(t_data *data);

void	init_lvl(t_data *data)
{
	t_pos		i;

	data->lvl = LVL_NORMAL;
	i = LVL_EASY;
	while (i <= LVL_HARD)
	{
		data->menu[i].pos = data->menu[i - 3].pos;
		data->menu[i].pos.y += PADY_LVL;
		data->menu[i].size = data->size_edit;
		i++;
	}
	data->menu[LVL_TITLE].pos = data->menu[FOV_TITLE].pos;
	data->menu[LVL_TITLE].pos.x -= PADX_LVL;
	data->menu[LVL_TITLE].pos.y += PADY_LVL;
	data->menu[LVL_BG].pos.x = data->menu[LVL_EASY].pos.x - MENU_PADX;
	data->menu[LVL_BG].pos.y = data->menu[LVL_EASY].pos.y - MENU_PADX;
	data->menu[LVL_BG].size.x = data->menu[LVL_EASY].size.x * 3 + MENU_PADX * 4;
	data->menu[LVL_BG].size.y = data->menu[LVL_EASY].size.y + MENU_PADX * 2;
	data->lvl_animation = FALSE;
	data->lvl_color[0] = (t_color){EASY_COLOR};
	data->lvl_color[1] = (t_color){NORMAL_COLOR};
	data->lvl_color[2] = (t_color){HARD_COLOR};
}

void	set_lvl_option(t_data *data)
{
	static int		i = 0;
	int				color;

	if (data->lvl_animation)
		color = get_gradient(data->lvl_color[data->prev_lvl - LVL_EASY], \
				data->lvl_color[data->lvl - LVL_EASY], i);
	else
		color = data->lvl_color[data->lvl - LVL_EASY].color;
	draw_round_rectangle((t_draw){&data->img, color, MENU_RADIUS + 4}, \
	data->menu[LVL_BG].pos, data->menu[LVL_BG].size);
	draw_alpha(&data->img, &data->lvls[3], data->menu[LVL_TITLE].pos);
	if (data->hover >= LVL_EASY && data->hover <= LVL_HARD \
			&& data->lvl != data->hover)
		draw_round_rectangle((t_draw){&data->img, FLOOR_COLOR, MENU_RADIUS}, \
			data->menu[data->hover].pos, data->menu[data->hover].size);
	if (data->lvl_animation)
		set_edit_animation(data, &i);
	else
		draw_round_rectangle((t_draw){&data->img, WALL_COLOR, MENU_RADIUS}, \
	data->menu[data->lvl].pos, data->menu[data->lvl].size);
	set_text_lvl(data);
}

static void	set_edit_animation(t_data *data, int *i)
{
	t_ico	p;

	if (*i == 0)
		data->start_animation = get_timestamp();
	sleep_until(*i * (FRAME / 1.5) + data->start_animation);
	p.x = animation(data->menu[data->prev_lvl].pos.x, \
		data->menu[data->lvl].pos.x, *i);
	p.y = data->menu[LVL_EASY].pos.y;
	draw_round_rectangle((t_draw){&data->img, WALL_COLOR, MENU_RADIUS}, \
		p, data->menu[LVL_EASY].size);
	++*i;
	if (*i == 29)
	{
		*i = 0;
		data->lvl_animation = FALSE;
	}
}

static void	set_text_lvl(t_data *data)
{
	t_pos	i;
	t_img	*f;
	t_ico	p;
	t_ico	s;

	i = LVL_EASY;
	while (i <= LVL_HARD)
	{
		p = data->menu[i].pos;
		s = data->menu[i].size;
		f = &data->lvls[i - LVL_EASY];
		p.x += (s.x / 2) - (f->width / 2);
		p.y += (s.y / 2) - (f->height / 2) + i - 4;
		if (f->img)
			draw_alpha(&data->img, f, p);
		i++;
	}
}
