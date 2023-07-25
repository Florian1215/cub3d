/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 20:06:44 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_keypress	get_keypress(int k);
void				change_map(t_data *data);

int	key_event(int k, t_data *data)
{
	(void)k;
	(void)data;
	return (SUCCESS);
}

int	key_event_press(int k, t_data *data)
{
	if (k == ESQ)
		close_mlx_success(data);
	else if (k == TAB)
		handle_menu(data);
	else if (get_keypress(k) != KP_ERROR)
		data->key_arrow_press[get_keypress(k)] = TRUE;
	else if (k == Q)
		change_map(data);
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
	const int	dict[KEYPRESS] = {UP_KEY, DOWN_KEY, LEFT_KEY, RIGHT_KEY, A, D};
	t_keypress	key;

	key = KP_UP;
	while (TRUE)
	{
		if (key == KEYPRESS)
			return (KP_ERROR);
		if (dict[key] == k)
			break ;
		key++;
	}
	return (key);
}
