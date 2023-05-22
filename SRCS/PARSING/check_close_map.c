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
//static t_ico	check_top(t_data *data);

t_exit	check_close_map(t_data *data)
{
//	t_ico	co;
//
//	co = check_top(data);
//	if (co .x == ERROR)
//		return (ERROR);
	(void)data;
	return (SUCCESS);
}

//static t_ico	check_top(t_data *data)
//{
//	t_ico	c;
//	t_bool	wall;
//
//	c = (t_ico){0, 0};
//	wall = FALSE;
//	while (c.x < data->width)
//	{
//		if (!wall && data->map[c.y][c.x] == WALL)
//			wall = TRUE;
//		if (wall && data->map[c.y][c.x] == NOTHING &&
//			data->map[c.y + 1][c.x - 1] == WALL)
//		{
//			printf("line good go left line\n");
//			return (c);
//		}
//		if (!wall && data->map[c.y][c.x] != WALL)
//			break ;
//		c.x++;
//	}
//	return ((t_ico){-1, -1});
//}
