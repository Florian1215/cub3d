/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:25:27 by mfinette          #+#    #+#             */
/*   Updated: 2023/08/29 14:20:13 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_data *data)
{
	int		i;
	double	width;
	double	edge_distance;
	int		color;
	double	wall_size;

	i = 0;
	width = (double)WIN_WIDTH / data->distances.size;
	while (i < data->distances.size)
	{
		if (data->distances.distance[i])
		{
			if (data->distances.distance[i] > 1)
				wall_size = WIN_HEIGHT / data->distances.distance[i] * 5;
			else
				wall_size = WIN_HEIGHT;
			// printf("\n\n\nWIN_HEIGHT = %d\n", WIN_HEIGHT);
			// printf("distance = %f\n", data->distances.distance[i]);
			// printf("wall_size = %f\n", wall_size);
			edge_distance = data->distances.distance[i] * 1.5;
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
			// printf("starting point = (%f,%f) ending point = (%f,%f)\n", i * width, (WIN_HEIGHT / 2) + (wall_size / 2), i * width, (WIN_HEIGHT / 2) + (wall_size / 2));
			draw_line(data, (t_dco){i * width, (WIN_HEIGHT / 2) - (wall_size / 2)}, \
				(t_dco){i * width, (WIN_HEIGHT / 2) + (wall_size / 2)}, color);
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
