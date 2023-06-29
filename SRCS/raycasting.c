/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:25:27 by mfinette          #+#    #+#             */
/*   Updated: 2023/06/28 17:56:39 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

t_dco	compute_coordinates(double x, double y)
{
	t_dco	co;

	co.x = x;
	co.y = y;
	return (co);
}

void	raycasting(t_data *data)
{
	int		i;
	double	width;
	double	edge_distance;
	int		color;

	i = 0;
	width = (double)WIN_WIDTH / data->distances->size;
	while (i < data->distances->size)
	{
		if (data->distances->distance[i])
		{
		edge_distance = data->distances->distance[i] * 2.5;
		if (edge_distance + 150 < WIN_HEIGHT - edge_distance - 150)
		{
			if (data->distances->face[i] == NORTH)
				color = 0x00FF00;
			else if (data->distances->face[i] == EAST)
				color = 0x0000FF;
			else if (data->distances->face[i] == WEST)
				color = 0xFF0000;
			else if (data->distances->face[i] == SOUTH)
				color = 0xFFFF00;
			else if (data->distances->face[i] == FACE_ERROR)
				color = 0xFFFFFF;
			draw_line(data, compute_coordinates(i * width, 0 + edge_distance + 150), \
				compute_coordinates(i * width, WIN_HEIGHT - edge_distance - 150), color);
		}
		else
		{
			draw_line(data, compute_coordinates(i * width, WIN_HEIGHT / 2 - 2), \
				compute_coordinates(i * width, WIN_HEIGHT / 2 + 2), 0xFF0000);
		}
		}
		i++;
	}
}
