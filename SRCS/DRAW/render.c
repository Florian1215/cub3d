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
	const char	*s[2] = {MSG_CLOSE_DOOR, MSG_OPEN_DOOR};
	t_ico		offset;

	offset = get_minimap_offset(data);
	print_background(data);
	rotate_player(data);
	move_player(data);
	raycasting(data);
	print_minimap(data, data->map, offset, TRUE);
	draw_fov(data, offset);
	print_minimap(data, data->map, offset, FALSE);
	print_player(data, data->map, offset);
	draw_square((t_draw){&data->img, WHITE, 0}, \
	data->v_pos, SIZE_V);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	if (data->door.is_scope)
		mlx_string_put(data->mlx_ptr, data->win_ptr, data->txt_pos.x, \
			data->txt_pos.y, WHITE, (char *)s[data->door.is_opening]);
}
