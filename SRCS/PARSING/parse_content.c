/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:09:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/18 19:09:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_exit	parse_color(t_map *map, char *line);

t_exit	parse_content(t_map *map, char *line)
{
	char const	*identifiers[6] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	char		*value;

	value = str_str(line, (char *)identifiers[map->state]);
	if (!value)
		return (error_msg(map->is_error_msg, ERR_MAP_ID, line));
	if (map->state <= PARSING_EA)
	{
		map->t[map->state].path = str_dup(value);
		if (!map->t[map->state].path)
			return (error_msg(map->is_error_msg, ERR_MALLOC));
	}
	else if (map->state == PARSING_FLOOR || map->state == PARSING_CEILING)
		return (parse_color(map, value));
	return (SUCCESS);
}

static t_exit	parse_color(t_map *map, char *line)
{
	char	**tab;

	tab = split_(line, ',');
	if (!tab)
		return (error_msg(map->is_error_msg, ERR_MALLOC));
	if (get_tab_size(tab) != 3)
		return (error_msg(map->is_error_msg, ERR_NB_ARGS));
	map->color[map->state - PARSING_FLOOR] = atoi_(tab[0]) << 16;
	map->color[map->state - PARSING_FLOOR] += atoi_(tab[1]) << 8;
	map->color[map->state - PARSING_FLOOR] += atoi_(tab[2]);
	free_split(tab);
	return (SUCCESS);
}
