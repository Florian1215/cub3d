/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:50:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 19:03:26 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

t_co	init_coordinate(double x, double y)
{
	t_co	co;

	co.x = x;
	co.y = y;
	return (co);
}

void	init_data(t_data *data)
{
	data->player_direction = NO_PLAYER;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, \
						"cub3d du bde c la follie");
	data->img.img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, \
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	data->key_arrow_press[LEFT] = FALSE;
	data->key_arrow_press[UP] = FALSE;
	data->key_arrow_press[RIGHT] = FALSE;
	data->key_arrow_press[DOWN] = FALSE;
}
