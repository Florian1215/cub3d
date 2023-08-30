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
	int	i;

	if (data->map->t[r->wall].is_texture)
	{
		i = 0;
		while (i < line_height)
		{
			(void)r->line.x;
			i++;
		}
	}
	else
		draw_line(data, r->line, (t_dco){r->line.x, r->line.y + \
			line_height}, data->map->t[r->wall].color);
}

void	load_texture(t_texture *t, char *filename, void *mlx_ptr, \
			t_parsing_state state)
{
	const int		colors[4] = {0xD0BFFF, NORMAL_COLOR, HARD_COLOR, 0xA8DF8E};

	init_img(&t->img, filename, mlx_ptr);
	if (!t->img.img)
	{
		t->is_texture = FALSE;
		t->color = colors[state];
	}
	else
		t->is_texture = TRUE;
}
