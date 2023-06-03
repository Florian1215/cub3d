/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_close_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:11:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/18 19:11:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/cub3d.h"

t_exit	check_close_map(t_data *data, t_ico p)
{
	if (p.y == 0 || p.y + 1 == data->height \
		|| p.x == 0 || p.x + 1 == data->width)
		return (ERROR);
	if (data->map[p.y][p.x + 1] == WALL && data->map[p.y + 1][p.x] \
			== WALL && data->map[p.y + 1][p.x + 1] != WALL)
		return (ERROR);
	data->map[p.y][p.x] = VALID;
	if (data->map[p.y][p.x + 1] == EMPTY_SPACE \
			&& check_close_map(data, (t_ico){p.x + 1, p.y}) == ERROR)
		return (ERROR);
	if (data->map[p.y][p.x - 1] == EMPTY_SPACE \
			&& check_close_map(data, (t_ico){p.x - 1, p.y}) == ERROR)
		return (ERROR);
	if (data->map[p.y + 1][p.x] == EMPTY_SPACE \
			&& check_close_map(data, (t_ico){p.x, p.y + 1}) == ERROR)
		return (ERROR);
	if (data->map[p.y - 1][p.x] == EMPTY_SPACE \
			&& check_close_map(data, (t_ico){p.x, p.y - 1}) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	clean_map(t_data *data)
{
	t_ico	i;

	i.y = 0;
	while (i.y < data->height)
	{
		i.x = 0;
		while (i.x < data->width)
		{
			if (data->map[i.y][i.x] == VALID)
				data->map[i.y][i.x] = EMPTY_SPACE;
			i.x++;
		}
		i.y++;
	}
}
