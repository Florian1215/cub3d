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
static void	print_square(t_data *data, t_co co, t_map value, int size);

void	print_minimap(t_data *data)
{
	t_co	i;
	int		square_size;

	i.x = 0;
	square_size = get_square_size(data);
	print_background(data);
	while (i.x < data->height)
	{
		i.y = 0;
		while (i.y < data->width)
		{
			print_square(
				data, \
				init_coordinate(i.y * square_size, i.x * square_size), \
				data->map[i.x][i.y], \
				square_size
				);
			i.y++;
		}
		i.x++;
	}
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
	t_co	i;

	i.x = 0;
	while (i.x < WIN_WIDTH)
	{
		i.y = 0;
		while (i.y < WIN_HEIGHT)
		{
			mlx_pixel_put_img(&data->img, i.x, i.y, 0x0B0B61);
			i.y++;
		}
		i.x++;
	}
}

static void	print_square(t_data *data, t_co co, t_map value, int size)
{
	const int	colors[5] = {0x045FB4, 0xFF0000, 0xD7DF01, 0x101010};
	const int	offset = 10;
	t_co		i;

	i.x = 0;
	while (i.x < size)
	{
		i.y = 0;
		while (i.y < size)
		{
			mlx_pixel_put_img(&data->img, offset + co.x + i.x, \
				offset + co.y + i.y, colors[value]);
			i.y++;
		}
		i.x++;
	}
}
