/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:49:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/16 17:49:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/cub3d.h"

void	print_background(t_data *data);

void	render(t_data *data)
{
	print_background(data);
	move_player(data);
	raycasting(data);
	print_minimap(data, data->map, (t_ico){MINIMAP_OFFSET, MINIMAP_OFFSET});
	if (!data->is_menu)
		draw_fov(data);
	print_player(data, data->map, (t_ico){MINIMAP_OFFSET, MINIMAP_OFFSET});
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}
