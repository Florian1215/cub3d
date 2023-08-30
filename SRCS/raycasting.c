/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:25:27 by mfinette          #+#    #+#             */
/*   Updated: 2023/08/30 15:11:05 by fguirama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define FOV		90

static void		draw_raycasting(t_data *data, t_dco pos, double angle, int i);
static void		check_horizontal(t_data *data, t_raycatsing *r, t_dco pos, double angle);
static void		check_vertical(t_data *data, t_raycatsing *r, t_dco pos, double angle);
static void		loop_until_hit_wall(t_map *map, t_raycatsing *r);
static double	fix_angle(double a);

void	raycasting(t_data *data)
{
	int 			i;
	t_dco 			pos;
	double			angle;


	angle = fix_angle(data->map->degre - FOV / 2);
	pos.x = (data->map->pos.x + data->map->hhitbox) / data->map->square_size;
	pos.y = (data->map->pos.y + data->map->hhitbox) / data->map->square_size;
	i = 0;
	while (i < WIN_WIDTH)
	{
		draw_raycasting(data, pos, angle, i);
		angle = fix_angle(angle + ((double)FOV / WIN_WIDTH));
		i++;
	}
}

static void	draw_raycasting(t_data *data, t_dco pos, double angle, int i)
{
	const int		colors[4] = {EASY_COLOR, NORMAL_COLOR, HARD_COLOR, WALL_COLOR};
	t_raycatsing	r[2];
	int				m;

	check_horizontal(data, r, pos, degre_to_radian(angle));
	check_vertical(data, r + 1, pos, degre_to_radian(angle));
	m = (r[0].co.x > r[1].co.y);
	float	ca = data->map->radian - degre_to_radian(angle);
	int		size_line = WIN_HEIGHT - data->map->hhitbox;
	r[m].distance *= cos(ca);
	int lineH = size_line / r[m].distance;
	if (lineH > size_line)
		lineH = size_line;
	int lineOff = WIN_HEIGHT / 2 - lineH / 2;
	draw_line(data, (t_dco){pos.x * data->map->square_size + MINIMAP_OFFSET, pos.y * data->map->square_size + MINIMAP_OFFSET}, (t_dco){r[m].co.x * data->map->square_size + MINIMAP_OFFSET, r[m].co.x  * data->map->square_size + MINIMAP_OFFSET}, FOV_COLOR);
	draw_line(data, (t_dco){i, lineOff}, (t_dco){i, lineH + lineOff}, colors[r[m].wall]);
}

static void	check_horizontal(t_data *data, t_raycatsing *r, t_dco pos, double angle)
{
	double	a_tan;

	r->distance = 10000;
	a_tan = -1.0 / tan(angle);
	if (angle > PI)
	{
		r->co.y = (int)pos.y - 0.00001;
		r->co.x = (pos.y - r->co.y) * a_tan + pos.x;
		r->step.y = -1;
		r->step.x = -r->step.y * a_tan;
		r->wall = WEST;
	}
	else if (angle < PI)
	{
		r->co.y = (int)pos.y + 1;
		r->co.x = (pos.y - r->co.y) * a_tan + pos.x;
		r->step.y = 1;
		r->step.x = -r->step.y * a_tan;
		r->wall = EAST;
	}
	else
	{
		r->co = pos;
		return ;
	}
	loop_until_hit_wall(data->map, r);
	r->distance = distance_between_points(pos, r->co);
}

static void	check_vertical(t_data *data, t_raycatsing *r, t_dco pos, double angle)
{
	t_dco	step;
	double	n_tan;

	r->distance = 10000;
	n_tan = -tan(angle);
	if (angle > PI2 && angle < PI3)
	{
		r->co.x = (int)pos.x - 0.00001;
		r->co.y = (pos.x - r->co.x) * n_tan + pos.y;
		step.x = -1;
		step.y = -step.x * n_tan;
		r->wall = NORTH;
	}
	else if (angle < PI2 || angle > PI3)
	{
		r->co.x = (int)pos.x + 1;
		r->co.y= (pos.x - r->co.x) * n_tan + pos.y;
		step.x = 1;
		step.y = -step.x * n_tan;
		r->wall = SOUTH;
	}
	else
	{
		r->co = pos;
		return ;
	}
	loop_until_hit_wall(data->map, r);
	r->distance = distance_between_points(pos, r->co);
}

static void	loop_until_hit_wall(t_map *map, t_raycatsing *r)
{
	int	i;

	i = 0;
	while (i < fmax(map->height, map->width))
	{
		if (is_wall_or_close_door(map, r->co))
			break ;
		r->co.x += r->step.x;
		r->co.y += r->step.y;
		i++;
	}
}

static double	fix_angle(double a)
{
	if (a >= 360)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}
