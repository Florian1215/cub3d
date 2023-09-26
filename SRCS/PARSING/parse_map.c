/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:06:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/17 16:06:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_exit			init_map(t_map *map);
static t_exit	parse_line_map(t_map *map, char *line, int k);
static t_case	get_char(t_map *map, char c);
static t_exit	check_close_map(t_map *map, t_ico p);
static void		clean_map(t_map *map);

t_exit	parse_map(t_map *map)
{
	t_list	*tmp;
	int		k;

	if (init_map(map))
		return (error_msg(map->is_error_msg, ERR_MALLOC));
	tmp = map->lst;
	k = 0;
	while (tmp)
	{
		if (parse_line_map(map, tmp->line, k) == ERROR)
			return (lst_clear(&map->lst), ERROR);
		tmp = tmp->next;
		k++;
	}
	lst_clear(&map->lst);
	if (map->degre == NO_PLAYER)
		return (error_msg(map->is_error_msg, ERR_NO_PLAYER));
	update_direction(map);
	if (check_close_map(map, map->start_pos) == ERROR)
		return (error_msg(map->is_error_msg, ERR_MAP_NO_CLOSE));
	clean_map(map);
	return (SUCCESS);
}

static t_exit	parse_line_map(t_map *map, char *line, int k)
{
	t_ico		i;

	i = (t_ico){0, 0};
	while (i.x < map->width)
	{
		if (line[i.y])
		{
			map->m[k][i.x] = get_char(map, line[i.y]);
			if (map->m[k][i.x] == INVALID_CHAR)
				return (error_msg(map->is_error_msg, \
					ERR_MAP_INVALID_CHAR, line[i.y]));
			if (map->m[k][i.x] == INVALID_PLAYER)
				return (error_msg(map->is_error_msg, ERR_TO_MANY_PLAYER));
			if (map->m[k][i.x] == PLAYER)
				set_player_position(map, k, i.x);
			i.y++;
		}
		else
			map->m[k][i.x] = NOTHING;
		i.x++;
	}
	return (SUCCESS);
}

static t_case	get_char(t_map *map, char c)
{
	if (c == '0')
		return (FLOOR);
	else if (c == '1')
		return (WALL);
	else if (c == 'D')
		return (DOOR_CLOSE);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (map->degre != NO_PLAYER)
			return (INVALID_PLAYER);
		if (c == 'E')
			map->degre = DEAST;
		else if (c == 'S')
			map->degre = DSOUTH;
		else if (c == 'W')
			map->degre = DWEST;
		else
			map->degre = DNORTH;
		return (PLAYER);
	}
	else if (c == ' ')
		return (NOTHING);
	else
		return (INVALID_CHAR);
}

static t_exit	check_close_map(t_map *map, t_ico p)
{
	if (p.y == 0 || p.y + 1 == map->height \
		|| p.x == 0 || p.x + 1 == map->width)
		return (ERROR);
	if (map->m[p.y][p.x + 1] == WALL && map->m[p.y + 1][p.x] \
		== WALL && map->m[p.y + 1][p.x + 1] != WALL)
		return (ERROR);
	if (map->m[p.y][p.x] == FLOOR)
		map->m[p.y][p.x] = CHECK_FLOOR;
	else
		map->m[p.y][p.x] = CHECK_DOOR;
	if ((map->m[p.y][p.x + 1] == FLOOR || map->m[p.y][p.x + 1] == DOOR_CLOSE) \
			&& check_close_map(map, (t_ico){p.x + 1, p.y}) == ERROR)
		return (ERROR);
	if ((map->m[p.y][p.x - 1] == FLOOR || map->m[p.y][p.x - 1] == DOOR_CLOSE) \
			&& check_close_map(map, (t_ico){p.x - 1, p.y}) == ERROR)
		return (ERROR);
	if ((map->m[p.y + 1][p.x] == FLOOR || map->m[p.y + 1][p.x] == DOOR_CLOSE) \
			&& check_close_map(map, (t_ico){p.x, p.y + 1}) == ERROR)
		return (ERROR);
	if ((map->m[p.y - 1][p.x] == FLOOR || map->m[p.y - 1][p.x] == DOOR_CLOSE) \
			&& check_close_map(map, (t_ico){p.x, p.y - 1}) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static void	clean_map(t_map *map)
{
	t_ico	i;

	i.y = 0;
	while (i.y < map->height)
	{
		i.x = 0;
		while (i.x < map->width)
		{
			if (map->m[i.y][i.x] == CHECK_FLOOR)
				map->m[i.y][i.x] = FLOOR;
			else if (map->m[i.y][i.x] == CHECK_DOOR)
				map->m[i.y][i.x] = DOOR_CLOSE;
			i.x++;
		}
		i.y++;
	}
}
