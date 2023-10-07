/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:06:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/25 17:06:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_direction(t_data *data)
{
	data->map->radian = degre_to_radian(data->map->degre);
	data->map->direction.x = cos(data->map->radian);
	data->map->direction.y = sin(data->map->radian);
	data->map->fov = dco_rotate(data->map->direction, \
degre_to_radian(data->fov_value.x));
}

void	rotate_player(t_data *data)
{
	if (data->keypress[KP_I] || data->keypress[KP_O])
	{
		if (data->keypress[KP_I])
			data->map->degre -= ROTATE_SPEED;
		if (data->keypress[KP_O])
			data->map->degre += ROTATE_SPEED;
		data->map->degre = rotate_degre(data->map->degre);
		update_direction(data);
	}
}

double	rotate_degre(double a)
{
	if (a < 0)
		a += 360;
	return (fmod(a, 360));
}
