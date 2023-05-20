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
