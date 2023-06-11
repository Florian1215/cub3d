/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:25:27 by mfinette          #+#    #+#             */
/*   Updated: 2023/06/10 17:31:29 by mfinette         ###   ########.fr       */
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

	i = 0;
	width = (double)WIN_WIDTH / data->distances->size;
	while (i < data->distances->size)
	{
		draw_line(data, compute_coordinates(i * width, 0 + data->distances->distance[i] * 2.5), \
			compute_coordinates(i * width, WIN_HEIGHT - data->distances->distance[i] * 2.5), data->distances->distance[i] * 10000);
		i++;
	}
}