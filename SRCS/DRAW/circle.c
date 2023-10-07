/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:02:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/16 18:02:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_value_circle(t_bool bool, int *start, int *end, int radius);

void	draw_circle(t_draw d, t_ico co)
{
	int	i;

	i = 0;
	while (i < 4)
		draw_qcircle(d, co, i++);
}

void	draw_qcircle(t_draw d, t_ico co, int q)
{
	int		sradius;
	t_ico	max;
	t_ico	i;

	sradius = ipow(d.radius, 2);
	set_value_circle(is_even(q), &i.x, &max.x, d.radius);
	while (i.x <= max.x)
	{
		set_value_circle(q < 2, &i.y, &max.y, d.radius);
		while (i.y <= max.y)
		{
			if (ipow(i.x, 2) + ipow(i.y, 2) <= sradius + 30)
				mlx_pixel_put_img(d.img, co.x + i.x + d.radius, \
					co.y + i.y + d.radius, d.color);
			i.y++;
		}
		i.x++;
	}
}

static void	set_value_circle(t_bool bool, int *start, int *end, int radius)
{
	if (bool)
	{
		*start = -radius;
		*end = 0;
	}
	else
	{
		*start = 0;
		*end = radius;
	}
}
