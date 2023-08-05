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
	const t_ico	size_fov = {100, 60};
	t_pos		i;

	i = FOV_70;
	while (i < 7)
	{
		data->menu[i].pos.x = right_pan + (size_fov.x * (i - 4)) + \
			(FOV_PADX * (i - 4)) + 5;
		data->menu[i].pos.y = data->menu[POS_4].pos.y + \
			data->fovs[3].height + 20;
		data->menu[i].size = size_fov;
		i++;
	}
	data->menu[FOV_TITLE].pos.x = data->menu[FOV_90].pos.x - 6;
	data->menu[FOV_TITLE].pos.y = data->menu[POS_4].pos.y + 10;
	data->menu[FOV_BG].pos.x = data->menu[FOV_70].pos.x - FOV_PADX;
	data->menu[FOV_BG].pos.y = data->menu[FOV_70].pos.y - FOV_PADX;
	data->menu[FOV_BG].size.x = data->menu[FOV_70].size.x * 3 + FOV_PADX * 4;
	data->menu[FOV_BG].size.y = data->menu[FOV_70].size.y + FOV_PADX * 2;
}

void	set_fov_option(t_data *data)
{
	draw_round_rectangle((t_draw){&data->img, BG_MAP_MENU, FOV_RADIUS + 4}, \
		data->menu[FOV_BG].pos, data->menu[FOV_BG].size);
	draw_alpha(&data->img, &data->fovs[3], data->menu[FOV_TITLE].pos);
	if (data->hover >= FOV_70 && data->hover <= FOV_110 \
			&& data->fov != data->hover)
		draw_round_rectangle((t_draw){&data->img, FLOOR_COLOR, FOV_RADIUS}, \
			data->menu[data->hover].pos, data->menu[data->hover].size);
	if (!data->fov_animation)
		draw_round_rectangle((t_draw){&data->img, WALL_COLOR, FOV_RADIUS}, \
			data->menu[data->fov].pos, data->menu[data->fov].size);
	if (data->fov_animation)
		set_fov_animation(data);
	set_text_fov(data);
}

static void	set_fov_animation(t_data *data)
{
	static int		i = 0;
	t_ico			p;

	if (i == 0)
		data->start_animation = get_timestamp();
	sleep_until(i * (FRAME / 1.5) + data->start_animation);
	p.x = animation(data->menu[data->prev_fov].pos.x, \
		data->menu[data->fov].pos.x, i);
	p.y = data->menu[FOV_70].pos.y;
	draw_round_rectangle((t_draw){&data->img, WALL_COLOR, FOV_RADIUS}, \
		p, data->menu[FOV_70].size);
	i++;
	if (i == 29)
	{
		i = 0;
		data->fov_animation = FALSE;
	}
}

static void	set_text_fov(t_data *data)
{
	t_pos	i;
	t_img	*f;
	t_ico	p;
	t_ico	s;

	i = FOV_70;
	while (i < 7)
	{
		p = data->menu[i].pos;
		s = data->menu[i].size;
		f = &data->fovs[i - 4];
		p.x += (s.x / 2) - (f->width / 2);
		p.y += (s.y / 2) - (f->height / 2);
		if (f->img)
			draw_alpha(&data->img, f, p);
		i++;
	}
}
