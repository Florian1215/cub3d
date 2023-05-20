/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:26:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 14:26:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	draw_square(t_data *data, t_co co, double size, t_color color)
{
	const int	offset = 10;
	int			x;
	int			y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			mlx_pixel_put_img(&data->img, offset + co.x + x, \
				offset + co.y + y, color.color);
			y++;
		}
		x++;
	}
}

void	plot_line(int x0, int y0, int x1, int y1)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	error;

	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	error = dx + dy;

	while true
		plot(x0, y0)
		if x0 == x1 && y0 == y1 break
	e2 = 2 * error
	if e2 >= dy
	if x0 == x1 break
	error = error + dy
	x0 = x0 + sx
	end if
		if e2 <= dx
	if y0 == y1 break
	error = error + dx
	y0 = y0 + sy
	end if
		end while
}
