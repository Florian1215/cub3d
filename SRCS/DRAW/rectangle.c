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

#include "../../INCLUDES/cub3d.h"

void	draw_rectangle(t_img *img, t_ico co, t_ico size, int color)
{
	t_ico	i;

	i.x = 0;
	while (i.x <= size.x)
	{
		i.y = 0;
		while (i.y <= size.y)
		{
			mlx_pixel_put_img(img, co.x + i.x, co.y + i.y, color);
			i.y++;
		}
		i.x++;
	}
}
