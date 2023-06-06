/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:27:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/06 20:27:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	handle_menu(t_data *data)
{
	data->is_menu = !data->is_menu;
	if (data->is_menu)
		set_menu(data);
}

void	set_menu(t_data *data)
{
	draw_square(data, (t_ico){0, 0}, WIN_WIDTH, 0xFF);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}
