/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:26:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 19:19:41 by mfinette         ###   ########.fr       */
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

//void plotLine(int x0, int y0, int x1, int y1)
// void	draw_line(t_data *data, t_co p0, t_co p1)
// {
// 	int dx =  abs_(p1.x - p0.x);
// 	int sx = p0.x < p1.x ? 1 : -1;
// 	int dy = -abs_(p1.y - p0.y);
// 	int	sy = p0.y < p1.y ? 1 : -1;
// 	int err = dx + dy;
// 	int	e2;

// 	while (TRUE)
// 	{
// 		mlx_pixel_put_img(&data->img, p0.x, p0.y, 0x0FFFFFF);
// 		if (p0.x == p1.x && p0.y == p1.y)
// 			break ;
// 		e2 = 2 * err;
// 		if (e2 >= dy)
// 		{
// 			err += dy;
// 			p0.x += sx;
// 		}
// 		if (e2 <= dx)
// 		{
// 			err += dx;
// 			p0.y += sy;
// 		}
// 	}
// }
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
			0x0FFFFFF);
		p1.x += delta.x;
		p1.y += delta.y;
	}
}


//void	draw_line(t_data *data, t_co p1, t_co p2)
//{
//	int	dx = abs_(p2.x - p1.x);
//	int	dy = abs_(p2.y - p1.x);
//	int	sx = p1.x < p2.x ? 1 : -1;
//	int	sy = p1.x < p2.y ? 1 : -1;
//	int	err = (dx > dy ? dx : -dy) / 2;
//	int	e2;
//
//	while (p1.x != p2.x || p1.y != p2.y)
//	{
//		mlx_pixel_put_img(&data->img, p1.x, p2.y, 0x0FFFFFF);
//		e2 = err;
//		if (e2 > -dx)
//		{
//			err -= dy;
//			p1.x += sx;
//		}
//		if (e2 < dy)
//		{
//			err += dx;
//			p1.x += sy;
//		}
//		if (p1.x == p2.x && p1.x == p2.y)
//			break ;
//	}
//}
