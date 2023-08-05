/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:04:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/18 16:04:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*map_new(void)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->degre = NO_PLAYER;
	new->m = NULL;
	new->texture_path[NORTH] = NULL;
	new->texture_path[SOUTH] = NULL;
	new->texture_path[WEST] = NULL;
	new->texture_path[EAST] = NULL;
	new->lst = NULL;
	new->state = NO;
	new->next = NULL;
	return (new);
}

void	map_add_back(t_map **start, t_map *new)
{
	if (!*start)
		*start = new;
	else
		map_last(*start)->next = new;
}

t_map	*map_last(t_map *m)
{
	if (!m || !m->next)
		return (m);
	return (map_last(m->next));
}

void	map_clear(t_map **map)
{
	t_map	*tmp;

	while (*map)
	{
		tmp = (*map)->next;
		free_n_split((void **)(*map)->m, (*map)->height - 1);
		free((*map)->texture_path[NORTH]);
		free((*map)->texture_path[SOUTH]);
		free((*map)->texture_path[WEST]);
		free((*map)->texture_path[EAST]);
		free(*map);
		*map = tmp;
	}
}

int	map_size(t_map *m)
{
	int	i;

	i = 0;
	while (m)
	{
		m = m->next;
		i++;
	}
	return (i);
}
