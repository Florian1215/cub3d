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
static t_face	valid_pos(t_map *map, t_dco pos);
t_bool			is_valid_pos(t_map *map, t_dco p1, t_dco p2);
static t_bool	make_valid_pos(t_map *map, t_dco *pos);
static t_face	get_face_pos(t_map *map, t_face vpos, t_dco pos);

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
			if (valid_pos(data->map, new_pos) == VALID_POS || \
					make_valid_pos(data->map, &new_pos))
				data->map->pos = new_pos;
		}
		k++;
	}
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

static t_face	valid_pos(t_map *map, t_dco pos)
{
	const t_face	faces[4] = {BOT_RIGHT, BOT_LEFT, TOP_RIGHT, TOP_LEFT};
	t_face			res;
	t_dco			hitbox;
	int				i;

	i = 0;
	res = VALID_POS;
	while (i < 4)
	{
		hitbox.x = map->hitbox * is_even(i);
		hitbox.y = map->hitbox * (i < 2);
		if (!is_valid_pos(map, pos, hitbox))
			res |= faces[i];
		i++;
	}
	return (res);
}

static t_bool	make_valid_pos(t_map *map, t_dco *pos)
{
	t_face	vpos;

	vpos = valid_pos(map, *pos);
	if (vpos == TOP_LEFT || vpos == TOP_RIGHT || \
			vpos == BOT_LEFT || vpos == BOT_RIGHT)
		vpos = get_face_pos(map, vpos, *pos);
	if (vpos == TOP)
		pos->y = ceil(pos->y);
	else if (vpos == BOT)
		pos->y = (int)pos->y;
	else if (vpos == LEFT)
		pos->x = ceil(pos->x);
	else if (vpos == RIGHT)
		pos->x = (int)pos->x;
	return (vpos == TOP || vpos == BOT || vpos == LEFT || vpos == RIGHT);
}

static t_face	get_face_pos(t_map *map, t_face vpos, t_dco pos)
{
	t_dco	hitbox;

	hitbox.x = map->hitbox * (vpos == TOP_RIGHT || vpos == BOT_RIGHT);
	hitbox.y = 2 + (map->hitbox - 4) * (vpos == BOT_LEFT || vpos == BOT_RIGHT);
	if (is_valid_pos(map, pos, hitbox))
	{
		if (vpos & TOP)
			return (TOP);
		return (BOT);
	}
	if (vpos & LEFT)
		return (LEFT);
	return (RIGHT);
}
