/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:30:22 by mfinette          #+#    #+#             */
/*   Updated: 2023/06/10 17:37:53 by mfinette         ###   ########.fr       */
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
	raycasting(data);
	while (x < data->height)
	{
		y = 0;
		while (y < data->width)
		{
			if (data->map[x][y] != NOTHING)
				draw_square(
					data, (t_dco){y * data->square_size, \
					x * data->square_size}, data->square_size,
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
	// const t_color	c[2] = {{0x198CA4}, {0x7E410B}};
	const	t_color	c[2] = {{0x00303030}, {0x00000000}};
	t_ico			i;

	i.x = 0;
	while (i.x < WIN_WIDTH)
	{
		i.y = 0;
		while (i.y < WIN_HEIGHT)
		{
			mlx_pixel_put_img(&data->img, i.x, i.y, \
				c[i.y > WIN_HEIGHT / 2].color);
			i.y++;
		}
		i.x++;
	}
}

int	get_map_coordinates(t_data *data, double co, double move)
{
	return ((int)((co + move + data->player.hhitbox) / data->square_size));
}
