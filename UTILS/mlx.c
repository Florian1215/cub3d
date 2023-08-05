/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:03:08 by mfinette          #+#    #+#             */
/*   Updated: 2023/05/17 19:03:19 by mfinette         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_pixel_put_img(t_img *img, int x, int y, int color)
{
	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;
	*(unsigned int *)(img->addr + (y * img->line_length + x * \
	(img->bits_per_pixel / 8))) = color;
}

int	close_mlx(t_data *data)
{
	map_clear(&data->map);
	free(data->distances.distance);
	free(data->distances.angle);
	free(data->distances.face);
	mlx_destroy_image(data->mlx_ptr, data->logo.img);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(SUCCESS);
}
