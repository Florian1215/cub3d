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

#include "../../INCLUDES/cub3d.h"

int	key_event(int k, t_data *data)
{
	(void)k;
	(void)data;
	return (SUCCESS);
}

int	key_event_press(int k, t_data *data)
{
	if (k == ESQ)
		close_mlx(data);
	else if (k == UP_KEY || k == DOWN_KEY || k == LEFT_KEY || k == RIGHT_KEY)
		data->key_arrow_press[k - LEFT_KEY] = TRUE;
	if (k == A || k == D)
	{
		rotate_player(k, data);
	}
	return (SUCCESS);
}

int	key_event_release(int k, t_data *data)
{
	if (k == UP_KEY || k == DOWN_KEY || k == LEFT_KEY || k == RIGHT_KEY)
		data->key_arrow_press[k - LEFT_KEY] = FALSE;
	return (SUCCESS);
}
