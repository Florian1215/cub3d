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

void	draw_alpha(t_img *img, t_img *alpha, t_ico pos, double ratio)
{
	t_ico	size;
	t_ico	texture;
	int		c;

	size = (t_ico){alpha->width * ratio, alpha->height * ratio};
	texture.y = 0;
	while (texture.y < size.y)
	{
		texture.x = 0;
		while (texture.x < size.x)
		{
			c = *(int *)(alpha->addr + (int)(texture.x / ratio) *alpha-> \
				bit_ratio + (int)(texture.y / ratio) *alpha->line_length);
			if (!(c & 0xFF000000))
				mlx_pixel_put_img(img, pos.x + texture.x, pos.y + texture.y, c);
			texture.x++;
		}
		texture.y++;
	}
}
