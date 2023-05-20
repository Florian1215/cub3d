/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:30:22 by mfinette          #+#    #+#             */
/*   Updated: 2023/05/18 16:36:46 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

static int	get_square_size(t_data *data);
static void	print_background(t_data *data);

void	print_minimap(t_data *data)
{
	const t_color	colors[3] = {{0x045FB4}, {0xFF0000}, {0x101010}};
	int				x;
	int				y;

	x = 0;
	data->square_size = get_square_size(data);
	print_background(data);
	while (x < data->height)
	{
		y = 0;
		while (y < data->width)
		{
			draw_square(
				data, \
				init_coordinate(y * data->square_size, x * data->square_size), \
				data->square_size,
				colors[data->map[x][y]]
				);
			y++;
		}
		x++;
	}
	print_player(data);
}

static int	get_square_size(t_data *data)
{
	int	max;

	if (data->height > data->width)
		max = data->height;
	else
		max = data->width;
	return (MINIMAP_SIZE / max);
}

static void	print_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			mlx_pixel_put_img(&data->img, x, y, 0x0B0B61);
			y++;
		}
		x++;
	}
}
