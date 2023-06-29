/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:47:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/16 17:47:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/cub3d.h"

void	draw_square(t_img *img, t_ico co, int size, int color)
{
	draw_rectangle(img, co, (t_ico){size, size}, color);
}

void	draw_round_square(t_img *img, t_ico co, int size, int radius, int color)
{
	int	dradius;

	dradius = radius * 2;
	draw_square(img, (t_ico){co.x + radius, co.y + radius}, size - \
		dradius, color);
	draw_rectangle(img, (t_ico){co.x + radius, co.y + size - radius}, \
		(t_ico){size - dradius, radius}, color);
	draw_qcircle(img, co, radius, 0, color);
	draw_rectangle(img, (t_ico){co.x + radius, co.y}, (t_ico){size - \
		dradius, radius}, color);
	draw_qcircle(img, (t_ico){co.x + size - dradius, co.y}, radius, 1, \
		color);
	draw_rectangle(img, (t_ico){co.x, co.y + radius}, (t_ico){radius, \
		size - dradius}, color);
	draw_qcircle(img, (t_ico){co.x, co.y + size - dradius}, radius, 2, \
		color);
	draw_rectangle(img, (t_ico){co.x + size - radius, co.y + radius}, \
		(t_ico){radius, size - dradius}, color);
	draw_qcircle(img, (t_ico){co.x + size - dradius, co.y + size - \
		dradius}, radius, 3, color);
}
