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

t_pos	select_map(t_data *data, t_ico click);
void	change_n_map(t_data *data, int n);

int	mouse_event_press(int button, int x, int y, t_data *data)
{
	t_pos	click;

	if (button == LEFT_CLICK && data->in_menu)
	{
		click = select_map(data, (t_ico){x, y});
		if (click != POS_ERROR)
		{
			change_n_map(data, click);
			data->launch_animation = TRUE;
			data->in_menu = FALSE;
		}
	}
	else if (button == LEFT_CLICK && !data->in_menu && x < MINIMAP_SIZE + \
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

int	mouse_event_motion(int x, int y, t_data *data)
{
	t_pos	hover;

	if (data->in_menu)
	{
		hover = select_map(data, (t_ico){x, y});
		if (hover != data->hover)
		{
			data->hover_animation = TRUE;
			data->hover = hover;
		}
	}
	return (SUCCESS);
}
