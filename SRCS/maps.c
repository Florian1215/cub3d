/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 22:07:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/05 22:07:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	change_n_map(t_data *data, int n);

t_exit	init_map(t_map *map)
{
	int	k;

	map->height = lst_size(map->lst);
	map->m = malloc(sizeof(t_map *) * map->height);
	if (!map->m)
		return (ERROR_MALLOC);
	map->width = lst_max_len(map->lst);
	k = 0;
	map->square_size = MINIMAP_SIZE / fmax(map->height, map->width);
	map->hitbox = map->square_size / 2;
	map->hhitbox = map->hitbox / 2 / map->square_size;
	while (k < map->height)
	{
		map->m[k] = malloc(sizeof(t_map) * map->width);
		if (!map->m[k])
			return (free_n_split((void **)map->m, k - 1), ERROR_MALLOC);
		k++;
	}
	return (SUCCESS);
}

void	launch_map(t_data *data, t_menus p)
{
	if (p >= data->n_map)
		return ;
	change_n_map(data, p);
	init_ratio(data);
	data->launch_animation = TRUE;
	data->in_menu = FALSE;
}

void	change_map(t_data *data)
{
	t_map	*tmp;

	if (!data->map->next || data->slide.animation)
		return ;
	data->slide.animation = TRUE;
	dup_img(&data->img, &data->slide.imgs[0]);
	tmp = data->map;
	data->map = data->map->next;
	tmp->next = NULL;
	map_last(data->map)->next = tmp;
}

static void	change_n_map(t_data *data, int n)
{
	t_map	*tmp;
	t_map	*prev;
	int		i;

	if (!n)
		return ;
	i = 0;
	tmp = data->map;
	while (i < n)
	{
		prev = tmp;
		tmp = tmp->next;
		i++;
	}
	prev->next = tmp->next;
	tmp->next = data->map;
	data->map = tmp;
}
