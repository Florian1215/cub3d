/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:24:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/08/30 18:24:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_texture(t_data *data, t_raycatsing *r, t_ico lineh, \
				double value);

void	init_texture(t_data *data, t_raycatsing *r, t_ico lineh)
{
	double	value;

//	if (r->is_active)
//		printf("%f - %f\n", r->pos.x, r->pos.y);
	if (r->wall == SOUTH || r->wall == NORTH)
		value = 1 - (r->pos.x - (int)r->pos.x);
	else
		value = 1 - (r->pos.y - (int)r->pos.y);
	if ((r->is_door || r->is_open_door) && data->door.is_animation && \
		data->door.co.x == (int)r->co_door.x && \
		data->door.co.y == (int)r->co_door.y)
	{
		if (data->door.is_opening && value < 0.5)
			value -= (data->door.pos - 50) / 100;
		else if (!data->door.is_opening && value < 0.5)
			value += (50 - data->door.pos) / 100;
		else
			value += (data->door.pos - 50) / 100;
	}
	draw_texture(data, r, lineh, value);
}

// TODO fix fisheye texture

static void	draw_texture(t_data *data, t_raycatsing *r, t_ico lineh, \
				double value)
{
	int		color;
	int		i;
	t_img	*t;
	t_ico	ct;

	t = &data->map->t[r->wall * !r->is_door + DOOR * r->is_door].img;
	i = 0;
	while (i < lineh.x)
	{
		ct.x = value * t->width;
		ct.y = (i + ((lineh.y - lineh.x) / 2)) * t->height / lineh.y;
		color = *(int *)(t->addr + ct.x * t->bit_ratio + ct.y * t->line_length);
		mlx_pixel_put_img(&data->img, r->line.x, (int)r->line.y + i, color);
		i++;
	}
}

void	load_textures(t_data *data)
{
	const int	colors[5] = {NORTH_COLOR, SOUTH_COLOR, WEST_COLOR, EAST_COLOR, \
							DOOR_CLOSE_COLOR};
	t_map		*m;
	t_wall		s;

	m = data->map;
	while (m)
	{
		s = NORTH;
		while (s <= DOOR)
		{
			if (m->t[s].path)
				init_img(&m->t[s].img, m->t[s].path, data->mlx_ptr);
			m->t[s].color = colors[s];
			m->t[s].is_texture = m->t[s].path && m->t[s].img.img;
			s++;
		}
		m = m->next;
	}
}
