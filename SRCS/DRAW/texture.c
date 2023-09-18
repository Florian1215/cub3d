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

void	draw_texture(t_data *data, t_raycatsing *r, int dlineh, int lineh)
{
	int		i;
	double	value;
	int		color;
	t_img	*t;
	t_ico	ct;

	(void)lineh;
	if (r->wall == SOUTH || r->wall == NORTH)
		value = r->co.x - (int)r->co.x;
	else
		value = r->co.y - (int)r->co.y;
	if (dlineh != lineh)
		lineh = dlineh + ((lineh - dlineh) * r->distance * 1.7);
	t = &data->map->t[r->wall].img;
	i = 0;
	while (i < dlineh)
	{
		ct.x = value * t->width;
		ct.y = (i + ((lineh - dlineh) / 2)) * t->height / lineh;
		color = *(int *)(t->addr + ct.x * t->bit_ratio + ct.y * t->line_length);
		mlx_pixel_put_img(&data->img, r->line.x, r->line.y + i, color);
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
			if (s != DOOR || m->t[s].path)
				init_img(&m->t[s].img, m->t[s].path, data->mlx_ptr);
			m->t[s].color = colors[s];
			m->t[s].is_texture = m->t[s].path && m->t->img.img;
			s++;
		}
		m = m->next;
	}
}
