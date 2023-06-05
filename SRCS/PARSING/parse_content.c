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

#include "../../INCLUDES/cub3d.h"

static t_exit	parse_color(t_map *map, char *line);

t_exit	parse_content(t_map *map, char *line)
{
	char const	*identifiers[6] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	char		*value;

	value = str_str(line, (char *)identifiers[map->state]);
	if (!value)
		return (ERROR);
	if (map->state <= EA)
	{
		map->texture_path[map->state] = str_dup(value);
		if (!map->texture_path[map->state])
			return (ERROR_MALLOC);
	}
	else if (map->state == FLOOR || map->state == CEILING)
		parse_color(map, value);
	return (SUCCESS);
}

static t_exit	parse_color(t_map *map, char *line)
{
	char	**tab;
	t_color	*color;

	if (map->state == FLOOR)
		color = &map->floor;
	else
		color = &map->ceiling;
	tab = split_(line, ',');
	if (!tab)
		return (ERROR_MALLOC);
	color->rgb.r = atoi_(tab[0]);
	color->rgb.g = atoi_(tab[1]);
	color->rgb.b = atoi_(tab[2]);
	free_split(tab);
	return (SUCCESS);
}
