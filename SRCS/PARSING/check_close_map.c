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

// TODO
static t_ico	find_start_wall(t_data *data);
static t_ico	check_wall(t_data *data, t_ico c);

t_exit	check_close_map(t_data *data)
{
	t_ico	start_wall;

	start_wall = find_start_wall(data);
	if (start_wall.x == -ERROR)
		return (ERROR);
	return (SUCCESS);
}

static t_ico	find_start_wall(t_data *data)
{
	t_ico	c;

	c = (t_ico){0, 0};
	while (c.x < data->width)
	{
		if (data->map[c.y][c.x] == WALL)
			return (c);
	}
	return ((t_ico){-1, -1});
}


static t_ico	check_wall(t_data *data, t_ico c)
{
	int	*i;
	int	*max;

	set_x(data, i, max);
	while (c.x < data->height)
	{
		if (wall && data->map[c.y][c.x] == NOTHING &&
			data->map[c.y + 1][c.x - 1] == WALL)
		{
			printf("line good go left line %d - %d\n", c.x , c.y);
			return (c);
		}
		if (!wall && data->map[c.y][c.x] != WALL)
			break ;
		c.x++;
	}
	return ((t_ico){-1, -1});
}

static void	set_x(t_data *data, int *i, int *max, t_ico c)
{
	*i = c.x;
	*max = data
}