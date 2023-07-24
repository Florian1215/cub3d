/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/18 19:23:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_map(t_data *data, t_ico click);

int	mouse_event_press(int button, int x, int y, t_data *data)
{
	if (button == LEFT_CLICK && data->is_menu)
		select_map(data, (t_ico){x, y});
	if (button == LEFT_CLICK && !data->is_menu && x < MINIMAP_SIZE + \
		MINIMAP_OFFSET && y < MINIMAP_SIZE + MINIMAP_OFFSET)
		handle_menu(data);
	return (SUCCESS);
}

int	mouse_event_release(int button, int x, int y, t_data *data)
{
	(void)button;
	(void)x;
	(void)y;
	(void)data;
	return (SUCCESS);
}

int	mouse_event_motion(int button, int x, int y, t_data *data)
{
	(void)button;
	(void)x;
	(void)y;
	(void)data;
	return (SUCCESS);
}
