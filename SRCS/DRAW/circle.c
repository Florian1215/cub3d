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

void	draw_circle(t_img *img, t_ico co, int radius, int color)
{
	int	i;

	i = 0;
	while (i < 4)
		draw_qcircle(img, co, radius, i++, color);
}

//i.x * i.x + i.y * i.y <= radius * radius

void	draw_qcircle(t_img *img, t_ico co, int radius, int q, int color)
{
	int		sradius;
	t_ico	max;
	t_ico	i;

	sradius = ipow(radius, 2);
	set_value_circle(is_even(q), &i.x, &max.x, radius);
	while (i.x <= max.x)
	{
		set_value_circle(q < 2, &i.y, &max.y, radius);
		while (i.y <= max.y)
		{
			if (ipow(i.x, 2) + ipow(i.y, 2) <= sradius + 30)
				mlx_pixel_put_img(img, co.x + i.x + radius, \
					co.y + i.y + radius, color);
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
