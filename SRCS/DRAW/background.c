/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:47:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/16 17:47:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_background(t_data *data)
{
	t_ico	i;

	i.x = 0;
	while (i.x < WIN_WIDTH)
	{
		i.y = 0;
		while (i.y < WIN_HEIGHT)
		{
			mlx_pixel_put_img(&data->img, i.x, i.y, \
				data->map->color[i.y > HWIN_HEIGHT]);
			i.y++;
		}
		i.x++;
	}
}
