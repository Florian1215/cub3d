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

#define SQSZ 5

void	print_background(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	(void)img;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
//			mlx_pixel_put_img(img, j, i, 0x0B0B61);
			j++;
		}
		i++;
	}
}

void	print_square(t_img *img, int x, int y, t_map value)
{
	const int	colors[5] = {0x045FB4, 0xFF0000, 0xD7DF01, 0x101010};
	int			i;
	int			j;
	int			size;

	i = 0;
	size = SQSZ;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			printf("%d - %d\n", x + i, y + j);
			mlx_pixel_put_img(img, x + i, y + j, colors[value]);
			j++;
		}
		i++;
	}
}

void	print_minimap(t_data *data)
{
	int	i;
	int	j;
	int	posx;
	int	posy;

	i = 0;
	print_background(data->img.img);
	posx = 0;
	posy = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			printf("(%d, %d) = %d\n", i, j, data->map[i][j]);
			print_square(data->img.img, posx + (j * SQSZ), posy + (i * SQSZ), data->map[i][j]);
			j++;
		}
		i++;
	}
}
