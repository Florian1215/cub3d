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

#include "cub3d.h"

t_ico	get_minimap_offset(t_data *data);
void	print_background(t_data *data);
void	rotate_player(t_data *data);
void	move_player(t_data *data);

void	render(t_data *data)
{
	t_ico	offset;

	offset = get_minimap_offset(data);
	print_background(data);
	rotate_player(data);
	move_player(data);
	raycasting(data);
	print_minimap(data, data->map, offset);
	draw_fov(data, (t_ico){offset.x + data->map->hhitbox, offset.y \
		+ data->map->hhitbox});
	print_player(data, data->map, offset);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}
