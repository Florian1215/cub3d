/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:35:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 14:47:22 by mfinette         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	parsing(&data, ac, av);
	init_data(&data);
	if (data.map->next)
		render_menu(&data);
	set_hook(&data);
	mlx_loop(data.mlx_ptr);
	return (SUCCESS);
}
