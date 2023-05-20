/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:03:08 by mfinette          #+#    #+#             */
/*   Updated: 2023/05/17 19:03:19 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	mlx_pixel_put_img(t_img *img, int x, int y, int color)
{
	if (x > WIN_WIDTH || x < 0 || y > WIN_HEIGHT || y < 0)
		return ;
	*(unsigned int *)(img->addr + (y * img->line_length + x * \
	(img->bits_per_pixel / 8))) = color;
}
