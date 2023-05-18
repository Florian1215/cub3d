/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:35:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/09 17:35:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDES/cub3d.h"

static void	init_data(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data);
	if (parsing(&data, ac, av) >= ERROR)
		return (ERROR); // TODO print message "Error\n"

	print_minimap(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);

	set_hook(&data);
	mlx_loop(data.mlx_ptr);
	return (SUCCESS);
}

static void	init_data(t_data *data)
{
	data->player_orientation = NO_PLAYER;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, \
						"cub3d du bde c la follie");
	data->img.img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, \
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
}
