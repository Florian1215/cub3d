/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:26:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 21:06:49 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	draw_square(t_data *data, t_co co, double size, t_color color)
{
	int			x;
	int			y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			mlx_pixel_put_img(&data->img, MINIMAP_OFFSET + co.x + x, MINIMAP_OFFSET + co.y + y, color.color);
			y++;
		}
		x++;
	}
}

void	draw_line(t_data *data, t_co p1, t_co p2)
{
	t_co	delta;
	float			max;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	max = fmax(fabs(delta.x), fabs(delta.y));
	delta.x /= max;
	delta.y /= max;
	while (((int)(p1.x - p2.x) || (int)(p1.y - p2.y)))
	{
		mlx_pixel_put_img(&data->img, (int)p1.x, (int)p1.y, \
			0x30888888);
		p1.x += delta.x;
		p1.y += delta.y;
	}
}
