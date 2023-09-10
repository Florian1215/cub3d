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

static void	mouse_event_menu(t_data *data, t_ico co, int button);
t_menus		select_binds(t_data *data, t_ico click);
void		launch_map(t_data *data, t_menus n);

int	mouse_event_press(int button, int x, int y, t_data *data)
{
	if (data->in_menu)
		mouse_event_menu(data, (t_ico){x, y}, button);
	else
	{
		if (button == LEFT_CLICK)
		{
			if (x < MINIMAP_SIZE + MINIMAP_OFFSET \
				&& y < MINIMAP_SIZE + MINIMAP_OFFSET)
				handle_menu(data);
			else
			{
				data->mouse_press = TRUE;
				data->mouse_cursor = x;
			}
		}
	}
	return (SUCCESS);
}

int	mouse_event_release(int button, int x, int y, t_data *data)
{
	(void)y;
	(void)data;
	if (!data->in_menu && button == LEFT_CLICK)
	{
		data->mouse_press = FALSE;
		data->mouse_cursor = x;
	}
	return (SUCCESS);
}

int	mouse_event_motion(int x, int y, t_data *data)
{
	t_menus	hover;

	if (data->in_menu)
	{
		hover = select_binds(data, (t_ico){x, y});
		if (hover != data->hover)
		{
			data->hover_animation = TRUE;
			data->hover = hover;
		}
	}
	else if (data->mouse_press)
	{
		data->map->degre += ((x - data->mouse_cursor) * 0.5) * -1;
		update_direction(data->map);
		data->mouse_cursor = x;
	}
	return (SUCCESS);
}

static void	mouse_event_menu(t_data *data, t_ico co, int button)
{
	t_menus		click;

	if (button == LEFT_CLICK)
	{
		click = select_binds(data, co);
		if (click >= POS_1 && click <= POS_4)
			launch_map(data, click);
		else if (!data->fov_animation && click >= FOV_70 \
					&& click <= FOV_110 && data->fov != click)
		{
			data->prev_fov = data->fov;
			data->fov = click;
			data->fov_animation = TRUE;
		}
		else if (!data->lvl_animation && click >= LVL_EASY \
					&& click <= LVL_HARD && data->lvl != click)
		{
			data->prev_lvl = data->lvl;
			data->lvl = click;
			data->lvl_animation = TRUE;
		}
	}
}
