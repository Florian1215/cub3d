/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:47:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/16 17:47:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(t_draw d, t_ico co, t_ico size)
{
	t_ico	i;

	i.x = 0;
	while (i.x <= size.x)
	{
		i.y = 0;
		while (i.y <= size.y)
		{
			mlx_pixel_put_img(d.img, co.x + i.x, co.y + i.y, d.color);
			i.y++;
		}
		i.x++;
	}
}

void	draw_round_rectangle(t_draw d, t_ico co, t_ico size)
{
	int	dradius;

	dradius = d.radius * 2;
	draw_rectangle(d, (t_ico){co.x + d.radius, co.y + d.radius}, \
		(t_ico){size.x - dradius, size.y - dradius});
	draw_rectangle(d, (t_ico){co.x + d.radius, co.y + size.y - \
		d.radius}, (t_ico){size.x - dradius, d.radius});
	draw_qcircle(d, co, 0);
	draw_rectangle(d, (t_ico){co.x + d.radius, co.y}, \
		(t_ico){size.x - dradius, d.radius});
	draw_qcircle(d, (t_ico){co.x + size.x - dradius, co.y}, 1);
	draw_rectangle(d, (t_ico){co.x, co.y + d.radius}, \
		(t_ico){d.radius, size.y - dradius});
	draw_qcircle(d, (t_ico){co.x, co.y + size.y - dradius}, 2);
	draw_rectangle(d, (t_ico){co.x + size.x - d.radius, co.y + d.radius}, \
		(t_ico){d.radius, size.y - dradius});
	draw_qcircle(d, (t_ico){co.x + size.x - dradius, co.y + \
		size.y - dradius}, 3);
}
