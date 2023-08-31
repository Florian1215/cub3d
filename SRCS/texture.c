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

void	draw_texture(t_data *data, t_raycatsing *r, int line_height)
{
	int		i;
	double	value;
	int		color;
	t_img	*t;
	t_ico	ct;

	if (r->wall == LEFT || r->wall == RIGHT)
		value = r->co.y - (int)r->co.y;
	else
		value = r->co.x - (int)r->co.x;
	i = 0;
	t = &data->map->t[r->wall].img;
//	printf("%f\n", value);
	while (i < line_height)
	{
		printf("%f - %d - %d\n", value, t->width, data->map->t[r->wall].img.width);
		ct = (t_ico){(int)(value * t->width), i * t->height / line_height};
		printf("%d - %d\n", ct.x, ct.y);
		color = *(int *)(t->addr + ct.x * t->bit_ratio + \
				ct.y * t->line_length);
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
			init_img(&m->t->img, m->t[s].path, data->mlx_ptr);
			printf("%d\n", m->t->img.width);
			m->t->color = colors[s];
			m->t->is_texture = m->t->img.img != NULL;
			s++;
		}
		m = m->next;
	}
}
