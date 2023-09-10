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
static t_side	valid_pos(t_map *map, t_dco pos);
static t_bool	make_valid_pos(t_map *map, t_dco *pos);
static t_side	get_face_pos(t_map *map, t_side vpos, t_dco pos);

void	move_player(t_data *data)
{
	const double	ts[4] = {0, PI, -PI2, PI2};
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
				dco_mul(direction, MOVE_SPEED));
			if (valid_pos(data->map, new_pos) == VALID_POS || \
					make_valid_pos(data->map, &new_pos))
				data->map->pos = new_pos;
		}
		k++;
	}
}

static t_dco	dco_rotate(t_dco co, double t)
{
	return ((t_dco){cosf(t) * co.x + -sinf(t) * co.y, \
		sinf(t) * co.x + cosf(t) * co.y});
}

static t_side	valid_pos(t_map *map, t_dco pos)
{
	const t_side	faces[4] = {TOP_LEFT, TOP_RIGHT, BOT_LEFT, BOT_RIGHT};
	t_side			res;
	t_dco			hitbox;
	int				i;

	i = 0;
	res = VALID_POS;
	while (i < 4)
	{
		hitbox.x = map->hhitbox;
		hitbox.y = hitbox.x;
		if (is_even(i))
			hitbox.x *= -1;
		if (i < 2)
			hitbox.y *= -1;
		if (!is_valid_pos(map, pos, hitbox))
			res |= faces[i];
		i++;
	}
	return (res);
}

static t_bool	make_valid_pos(t_map *map, t_dco *pos)
{
	t_side	vpos;

	vpos = valid_pos(map, *pos);
	if (vpos == TOP_LEFT || vpos == TOP_RIGHT || \
			vpos == BOT_LEFT || vpos == BOT_RIGHT)
		vpos = get_face_pos(map, vpos, *pos);
	if (vpos == TOP)
		pos->y = ceil(pos->y - map->hhitbox) + map->hhitbox;
	if (vpos == BOT)
		pos->y = (int)(pos->y + map->hhitbox) - map->hhitbox;
	if (vpos == LEFT)
		pos->x = ceil(pos->x - map->hhitbox) + map->hhitbox;
	if (vpos == RIGHT)
		pos->x = (int)(pos->x + map->hhitbox) - map->hhitbox;
	return (vpos == TOP || vpos == BOT || vpos == LEFT || vpos == RIGHT);
}

static t_side	get_face_pos(t_map *map, t_side vpos, t_dco pos)
{
	t_dco	hitbox;

	hitbox.x = map->hhitbox;
	hitbox.y = map->hhitbox - 0.1;
	if (vpos == TOP_LEFT || vpos == BOT_LEFT)
		hitbox.x *= -1;
	if (vpos == TOP_LEFT || vpos == TOP_RIGHT)
		hitbox.y *= -1;
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
