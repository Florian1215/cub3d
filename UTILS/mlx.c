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
	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	*(unsigned int *)(img->addr + (y * img->line_length + x * \
	(img->bits_per_pixel / 8))) = color;
}

int	close_mlx(t_data *data)
{
	map_clear(&data->map, data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->slide.imgs[0].img);
	mlx_destroy_image(data->mlx_ptr, data->logo.img);
	mlx_destroy_image(data->mlx_ptr, data->fov.imgs[0].img);
	mlx_destroy_image(data->mlx_ptr, data->fov.imgs[1].img);
	mlx_destroy_image(data->mlx_ptr, data->fov.imgs[2].img);
	mlx_destroy_image(data->mlx_ptr, data->fov.imgs[3].img);
	mlx_destroy_image(data->mlx_ptr, data->lvl.imgs[0].img);
	mlx_destroy_image(data->mlx_ptr, data->lvl.imgs[1].img);
	mlx_destroy_image(data->mlx_ptr, data->lvl.imgs[2].img);
	mlx_destroy_image(data->mlx_ptr, data->lvl.imgs[3].img);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(SUCCESS);
}

void	dup_img(t_img *img1, t_img *img2)
{
	t_ico	i;
	int		c;

	i.x = 0;
	while (i.x < WIDTH)
	{
		i.y = 0;
		while (i.y < HEIGHT)
		{
			c = *(int *)(img1->addr + i.x * img1->bit_ratio + i.y * \
				img1->line_length);
			*(int *)(img2->addr + i.x * img2->bit_ratio + i.y * \
				img2->line_length) = c;
			i.y++;
		}
		i.x++;
	}
}
