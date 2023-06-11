/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:26:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/05 15:30:08 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	draw_square(t_data *data, t_dco co, double size, t_color color)
{
	t_ico	i;

	i.x = 0;
	while (i.x < size)
	{
		i.y = 0;
		while (i.y < size)
		{
			mlx_pixel_put_img(&data->img, MINIMAP_OFFSET + co.x + i.x, \
				MINIMAP_OFFSET + co.y + i.y, color.color);
			i.y++;
		}
		i.x++;
	}
}

void	draw_line(t_data *data, t_dco p1, t_dco p2, int color)
{
	t_dco	delta;
	float	max;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	max = fmax(fabs(delta.x), fabs(delta.y));
	delta.x /= max;
	delta.y /= max;
	while (((int)(p1.x - p2.x) || (int)(p1.y - p2.y)))
	{
		mlx_pixel_put_img(&data->img, (int)p1.x, (int)p1.y,
			color);
		p1.x += delta.x;
		p1.y += delta.y;
	}
}
