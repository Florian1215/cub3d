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

static t_exit	parse_color(t_data *data, char *line, t_parsing_state state);

t_exit	parse_content(t_data *data, char *line, t_parsing_state state)
{
	char const	*identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	char		**tab;

	if (!str_str(line, identifiers[state]))
		return (ERROR);
	tab = split_(line, ' ');
	if (!tab)
		return (ERROR_MALLOC);
	if (!tab[1])
		return (free_split(tab), ERROR);
	if (state <= EA)
	{
		data->texture_path[state] = str_dup(tab[1]);
		if (!data->texture_path[state])
			return (free_split(tab), ERROR_MALLOC);
	}
	else if (state == FLOOR || state == CEILING)
		parse_color(data, tab[1], state);
	return (free_split(tab), SUCCESS);
}

static t_exit	parse_color(t_data *data, char *line, t_parsing_state state)
{
	char	**tab;
	t_color	*color;

	if (state == FLOOR)
		color = &data->floor;
	else
		color = &data->ceiling;
	tab = split_(line, ',');
	if (!tab)
		return (ERROR_MALLOC);
	color->rgb.r = atoi_(tab[0]);
	color->rgb.g = atoi_(tab[1]);
	color->rgb.b = atoi_(tab[2]);
	free_split(tab);
	return (SUCCESS);
}
