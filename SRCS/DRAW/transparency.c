/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:15:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/08/05 18:15:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_alpha(t_img *img, t_img *alpha, t_ico pos)
{
	t_ico	i;
	t_ico	texture;
	int		c;

	i.y = pos.y;
	texture.y = 0;
	while (texture.y < alpha->height)
	{
		i.x = pos.x;
		texture.x = 0;
		while (texture.x < alpha->width)
		{
			c = *(int *)(alpha->addr + texture.x * alpha->bit_ratio + \
				texture.y * alpha->line_length);
			if (!(c & 0xFF000000))
				mlx_pixel_put_img(img, i.x, i.y, c);
			i.x++;
			texture.x++;
		}
		i.y++;
		texture.y++;
	}
}
