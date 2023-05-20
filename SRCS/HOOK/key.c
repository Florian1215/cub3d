/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/18 19:23:00 by fguirama         ###   ########lyon.fr   */
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
	return (SUCCESS);
}

int	key_event_release(int k, t_data *data)
{
	if (k == UP_KEY || k == DOWN_KEY || k == LEFT_KEY || k == RIGHT_KEY)
		data->key_arrow_press[k - LEFT_KEY] = FALSE;
	return (SUCCESS);
}
