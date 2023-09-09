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
	t = &data->map->t[r->wall].img;
	i = 0;
//	printf("%f\n", sqrt(lineh - dlineh));
//	lineh = (lineh - dlineh) / 1.4 + dlineh;
	while (i < dlineh)
	{
		ct.x = value * t->width;
		ct.y = (i + ((lineh - dlineh) / 2)) * t->height / lineh;
//		ct.y = i * t->height / dlineh;
		color = *(int *)(t->addr + ct.x * t->bit_ratio + ct.y * t->line_length);
		mlx_pixel_put_img(&data->img, r->line.x, r->line.y + i, color);
		i++;
	}
}

void	load_textures(t_data *data)
{
	const int		colors[4] = {0xD0BFFF, NORMAL_COLOR, HARD_COLOR, 0xA8DF8E}; // TODO COLOR !!
	t_map			*m;
	t_parsing_state	s;

	m = data->map;
	while (m)
	{
		s = PARSING_NO;
		while (s <= PARSING_EA)
		{
			init_img(&m->t[s].img, m->t[s].path, data->mlx_ptr);
			m->t[s].color = colors[s];
			m->t[s].is_texture = m->t->img.img != NULL;
			s++;
		}
		m = m->next;
	}
}
