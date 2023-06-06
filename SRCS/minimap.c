/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:30:22 by mfinette          #+#    #+#             */
/*   Updated: 2023/05/20 16:10:23 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"


void	print_minimap(t_data *data)
{
	const t_color	colors[3] = {{0x045FB4}, {0xFF0000}, {0x101010}};
	int				x;
	int				y;

	x = 0;
//	printf("salut %f\n", data->map->direction);

	while (x < data->map->height)
	{
		y = 0;
		while (y < data->map->width)
		{
			if (data->map->m[x][y] != NOTHING)
				draw_square(data, (t_ico){MINIMAP_OFFSET + y * data->map \
				->square_size, MINIMAP_OFFSET + x * data->map->square_size}, \
				data->map->square_size, colors[data->map->m[x][y]].color);
			y++;
		}
		x++;
	}
}

int	get_map_coordinates(t_data *data, double co, double move)
{
	return ((int)((co + move + data->map->hhitbox) \
		/ data->map->square_size));
}
