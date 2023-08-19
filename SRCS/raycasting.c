/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:25:27 by mfinette          #+#    #+#             */
/*   Updated: 2023/08/19 19:45:12 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_data *data)
{
	int		i;
	double	width;
	double	edge_distance;
	int		color;

	i = 0;
	width = (double)WIN_WIDTH / data->distances.size;
	while (i < data->distances.size)
	{
		if (data->distances.distance[i])
		{
			edge_distance = data->distances.distance[i] * 1.5;
			// if (edge_distance + 150 < WIN_HEIGHT - edge_distance - 150)
			// {
				if (data->distances.face[i] == NORTH)
					color = 0x00FF00;
				else if (data->distances.face[i] == EAST)
					color = 0x0000FF;
				else if (data->distances.face[i] == WEST)
					color = 0xFF0000;
				else if (data->distances.face[i] == SOUTH)
					color = 0xFFFF00;
				else if (data->distances.face[i] == FACE_ERROR)
					color = 0xFFFFFF;
				draw_line(data, (t_dco){i * width, fmin(edge_distance, WIN_HEIGHT / 2)}, \
				(t_dco){i * width, fmax(WIN_HEIGHT - edge_distance, WIN_HEIGHT / 2)}, color);
			// }
			// else
			// {
			// 	draw_line(data, (t_dco){i * width, WIN_HEIGHT / 2 - 2}, \
			// 		(t_dco){i * width, WIN_HEIGHT / 2 + 2}, 0xFF0000);
			// }
		}
		i++;
	}
}
