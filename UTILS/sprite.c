/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/10/02 17:23:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_sprite	*sprite_new(t_ico i);
static void		sprite_add_back(t_sprite **start, t_sprite *new);

void	init_sprite(t_map *map, int y, int x)
{
	t_sprite	*new;

	map->m[y][x] = FLOOR;
	new = sprite_new((t_ico){x, y});
	if (new)
		sprite_add_back(&map->s, new);
}

static t_sprite	*sprite_new(t_ico i)
{
	t_sprite	*new;

	new = malloc(sizeof(t_sprite));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->is_collected = FALSE;
	new->side = 1;
	new->y = 0;
	new->co = (t_dco){i.x + 0.5, i.y + 0.5};
	return (new);
}

static void	sprite_add_back(t_sprite **start, t_sprite *new)
{
	if (!*start)
		*start = new;
	else
		sprite_last(*start)->next = new;
}

t_sprite	*sprite_last(t_sprite *m)
{
	if (!m || !m->next)
		return (m);
	return (sprite_last(m->next));
}

void	sprite_clear(t_sprite **sprite, void *mlx_ptr)
{
	t_sprite	*tmp;

	(void)mlx_ptr;
	while (sprite && *sprite)
	{
		tmp = (*sprite)->next;
		free(*sprite);
		*sprite = tmp;
	}
}
