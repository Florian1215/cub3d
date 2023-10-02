/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/08/29 13:46:10 by mfinette         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO change FOV work

void	draw_fov(t_data	*data, t_ico offset)
{
	int				i;

	i = 0;
	while (i < WIDTH)
	{
		draw_line(data, get_map_dco(data->map, offset), (t_dco) \
		{data->fov_line[i].x * data->map->square_size + offset.x, \
		data->fov_line[i].y * data->map->square_size + offset.y}, \
		FOV_COLOR);
		i++;
	}
}
