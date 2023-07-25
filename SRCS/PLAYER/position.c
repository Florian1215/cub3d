/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:05:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/25 17:05:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_dco	dco_rotate(t_dco co, double t);
static t_bool	is_valid_pos(t_map *map, t_dco pos);

void	move_player(t_data *data)
{
	const double	ts[4] = {0, M_PI, -M_PI_2, M_PI_2};
	t_dco			new_pos;
	t_dco			direction;
	t_keypress		k;

	k = KP_UP;
	while (k < 4)
	{
		if (data->key_arrow_press[k])
		{
			if (k == KP_UP)
				direction = data->map->direction;
			else
				direction = dco_rotate(data->map->direction, ts[k]);
			new_pos = dco_add(data->map->pos, \
				dco_mul(direction, data->map->move_speed));
			if (is_valid_pos(data->map, new_pos))
				data->map->pos = new_pos;
		}
		k++;
	}
}

static t_bool	is_valid_pos(t_map *map, t_dco pos)
{
	t_dco	hitbox;
	int		i;

	i = 0;
	while (i < 4)
	{
		hitbox.x = map->hitbox * is_even(i);
		hitbox.y = map->hitbox * (i < 2);
		if (map->m[(int)((pos.y + hitbox.y) / map->square_size)] \
				[(int)((pos.x + hitbox.x) / map->square_size)] != EMPTY_SPACE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_dco	dco_rotate(t_dco co, double t)
{
	double	m[2][2];

	m[0][0] = cosf(t);
	m[0][1] = -sinf(t);
	m[1][0] = sinf(t);
	m[1][1] = cosf(t);
	return ((t_dco){m[0][0] * co.x + m[0][1] * co.y, \
		m[1][0] * co.x + m[1][1] * co.y});
}
