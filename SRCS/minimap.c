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

static void	print_background(t_data *data);

void	print_minimap(t_data *data)
{
	const t_color	colors[3] = {{0x045FB4}, {0xFF0000}, {0x101010}};
	int				x;
	int				y;

	x = 0;
	print_background(data);
	while (x < data->height)
	{
		y = 0;
		while (y < data->width)
		{
			if (data->map[x][y] != NOTHING)
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}

static void	print_background(t_data *data)
{
	const t_color	c[2] = {{0x198CA4}, {0x7E410B}};
	int				x;
	int				y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			mlx_pixel_put_img(&data->img, x, y, c[y > WIN_HEIGHT / 2].color);
			y++;
		}
		x++;
	}
}

int	get_square_size(t_data *data)
{
	int	max;

	if (data->height > data->width)
		max = data->height;
	else
		max = data->width;
	return (MINIMAP_SIZE / max);
}
