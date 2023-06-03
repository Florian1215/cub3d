/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:35:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 14:47:22 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDES/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data);
	if (parsing(&data, ac, av) >= ERROR)
		return (print_error("Error", NULL)); // TODO print message "Error\n"
	print_minimap(&data);
	set_hook(&data);
	mlx_loop(data.mlx_ptr);
	return (SUCCESS);
}
