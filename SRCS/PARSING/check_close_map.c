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
static t_exit	check_right(t_data *data, t_ico *c);
static t_exit	check_left(t_data *data, t_ico *c);
static t_exit	check_up(t_data *data, t_ico *c);
static t_exit	check_down(t_data *data, t_ico *c);

t_exit	check_close_map(t_data *data)
{
	t_ico	start_wall;

	start_wall = find_start_wall(data);
	if (start_wall.x == -ERROR)
		return (ERROR);
	return (check_right(data, &start_wall));
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


static t_exit	check_right(t_data *data, t_ico *c)
{
	t_exit	res_status;

	while (TRUE)
	{
		printf("%d | %d - %d\n", data->map[c->y][c->x],  c->y, c->x);
		if (data->map[c->y][c->x] == WALL && (c->x + 1 == data->width || data->map[c->y][c->x + 1] != WALL))
		{
			if (c->y != 0 && data->map[c->y - 1][c->x] == WALL)
				res_status = check_up(data, c);
			else if (c->y + 1 < data->height && data->map[c->y + 1][c->x] == WALL)
				res_status = check_down(data, c);
			else
				return (ERROR);
			if (res_status == ERROR)
				return (ERROR);
		}
		c->x++;
	}
}

static t_exit	check_left(t_data *data, t_ico *c)
{
	t_exit	res_status;

	while (TRUE)
	{
		printf("%d | %d - %d\n", data->map[c->y][c->x],  c->y, c->x);
		if (data->map[c->y][c->x] == WALL && (c->x == 0 || data->map[c->y][c->x - 1] != WALL))
		{
			if (c->y != 0 && data->map[c->y - 1][c->x] == WALL)
				res_status = check_up(data, c);
			else if (c->y + 1 < data->height && data->map[c->y + 1][c->x] == WALL)
				res_status = check_down(data, c);
			else
			{
				printf("finish left\n");
				return (SUCCESS);
			}
			if (res_status == ERROR)
				return (ERROR);
		}
		c->x--;
	}
}

static t_exit	check_up(t_data *data, t_ico *c)
{
	t_exit	res_status;

	while (TRUE)
	{
		printf("%d | %d - %d\n", data->map[c->y][c->x],  c->y, c->x);
		if (data->map[c->y][c->x] == WALL && (c->y == 0 || data->map[c->y - 1][c->x] != WALL))
		{
			if (c->y != 0 && data->map[c->y - 1][c->x] == WALL)
				res_status = check_up(data, c);
			else if (c->y + 1 < data->height && data->map[c->y + 1][c->x] == WALL)
				res_status = check_down(data, c);
			else
			{
				printf("finish up\n");
				return (SUCCESS);
			}
			if (res_status == ERROR)
				return (ERROR);
		}
		c->y--;
	}
}

static t_exit	check_down(t_data *data, t_ico *c)
{
	t_exit	res_status;

	while (TRUE)
	{
		printf("%d | %d - %d\n", data->map[c->y][c->x],  c->y, c->x);
		if (data->map[c->y][c->x] == WALL && (c->y + 1 == data->height || data->map[c->y + 1][c->x] != WALL))
		{
			if (c->x != 0 && data->map[c->y][c->x - 1] == WALL)
				res_status = check_left(data, c);
			else if (c->x + 1 < data->width && data->map[c->y][c->x + 1] == WALL)
				res_status = check_right(data, c);
			else
			{
				printf("finish down\n");
				return (SUCCESS);
			}
			if (res_status == ERROR)
				return (ERROR);
		}
		c->y++;
	}
}
