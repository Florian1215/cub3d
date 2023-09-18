/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 20:06:44 by mfinette         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_keypress	get_keypress(int k);
void				change_map(t_data *data);
void				launch_map(t_data *data, t_menus n);

int	key_event_press(int k, t_data *data)
{
	if (k == ESQ)
		close_mlx(data);
	else if (k == TAB)
		handle_menu(data);
	else if (data->in_menu)
	{
		if (k == PAV_1 || k == NUM_1)
			launch_map(data, POS_1);
		else if (k == PAV_2 || k == NUM_2)
			launch_map(data, POS_2);
		else if (k == PAV_3 || k == NUM_3)
			launch_map(data, POS_3);
		else if (k == PAV_4 || k == NUM_4)
			launch_map(data, POS_4);
	}
	else
	{
		if (get_keypress(k) != KP_ERROR)
			data->key_arrow_press[get_keypress(k)] = TRUE;
		else if (k == Q)
			change_map(data);
//		else if (k == E)
//			toggle_door();
	}
	return (SUCCESS);
}

int	key_event_release(int k, t_data *data)
{
	if (get_keypress(k) != KP_ERROR)
		data->key_arrow_press[get_keypress(k)] = FALSE;
	return (SUCCESS);
}

static t_keypress	get_keypress(int k)
{
	const int	dic[KEYPRESS] = {W, S, A, D, LEFT_KEY, RIGHT_KEY};
	t_keypress	key;

	key = KP_UP;
	while (key < KEYPRESS)
	{
		if (dic[key] == k)
			return (key);
		key++;
	}
	return (KP_ERROR);
}
