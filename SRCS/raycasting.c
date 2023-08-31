/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:25:27 by mfinette          #+#    #+#             */
/*   Updated: 2023/08/30 15:11:05 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_raycasting(t_data *data, t_dco pos, double angle, int i);
void		draw_texture(t_data *data, t_raycatsing *r, int dlineh, int lineh);
static void	check_horizontal(t_data *data, t_raycatsing *r, t_dco pos, \
				double angle);
static void	check_vertical(t_data *data, t_raycatsing *r, t_dco pos, \
				double angle);
static void	loop_until_hit_wall(t_map *map, t_raycatsing *r);

void	raycasting(t_data *data)
{
	const double	fovs[3] = {70, 90, 110};
	int				i;
	t_dco			pos;
	double			angle;
//	double			ratio_horizontal;

	// TODO animation start
	angle = rotate_degre(data->map->degre - fovs[data->fov - FOV_70] / 2);
	pos.x = (data->map->pos.x + data->map->hhitbox) / data->map->square_size;
	pos.y = (data->map->pos.y + data->map->hhitbox) / data->map->square_size;
//	ratio_horizontal = 2 * tan(fovs[data->fov - FOV_70] / 2) / WIN_WIDTH;
//	ratio_horizontal = 2 * tan(fovs[data->fov - FOV_70] / 2) / WIN_WIDTH;
//	printf("RATIO %f | DIRECTION %f\n", ratio_horizontal, data->map->degre);
	i = 0;

	while (i < WIN_WIDTH)
	{
		// TODO fisheye
//		angle = radian_to_degre(atan((WIN_WIDTH - i) * ratio_horizontal));
//		printf("ANGLE %f ", angle);
//		angle = rotate_degre(data->map->degre + fovs[data->fov - FOV_70] / 2 - angle);
//		printf("| FINAL %f\n", angle);
		draw_raycasting(data, pos, angle, i);
		angle = rotate_degre(angle + (fovs[data->fov - FOV_70] / WIN_WIDTH));
		i++;
	}
}

static void	draw_raycasting(t_data *data, t_dco pos, double angle, int i)
{
	t_raycatsing	r[2];
	int				m;
	int				line_height;
	int				draw_line_height;

	check_horizontal(data, r, pos, degre_to_radian(angle));
	check_vertical(data, r + 1, pos, degre_to_radian(angle));
	m = (r[0].distance > r[1].distance);
	r[m].distance *= cos(data->map->radian - degre_to_radian(angle));
	line_height = WIN_HEIGHT / r[m].distance;
	if (line_height > WIN_HEIGHT)
		draw_line_height = WIN_HEIGHT;
	else
		draw_line_height = line_height;
	r[m].line = (t_dco){i, WIN_HEIGHT / 2 - draw_line_height / 2};
	if (data->map->t[r->wall].is_texture)
		draw_texture(data, r + m, draw_line_height, line_height);
	else
		draw_line(data, r[m].line, (t_dco){r[m].line.x, r[m].line.y + \
			draw_line_height}, data->map->t[r[m].wall].color);
	data->fov_line[i] = (t_dco){r[m].co.x + (r[m].step.x / data->map-> \
		square_size), r[m].co.y + (r[m].step.y / data->map->square_size)};
}

static void	check_horizontal(t_data *data, t_raycatsing *r, t_dco pos, \
				double angle)
{
	double	a_tan;

	r->distance = 10000;
	a_tan = -1.0 / tan(angle);
	if (angle > PI)
	{
		r->co.y = (int)pos.y - 0.0000001;
		r->co.x = (pos.y - r->co.y) * a_tan + pos.x;
		r->step.y = -1;
		r->step.x = -r->step.y * a_tan;
		r->wall = SOUTH;
	}
	else if (angle < PI)
	{
		r->co.y = (int)pos.y + 1;
		r->co.x = (pos.y - r->co.y) * a_tan + pos.x;
		r->step.y = 1;
		r->step.x = -r->step.y * a_tan;
		r->wall = NORTH;
	}
	else
	{
		r->co = pos;
		r->wall = WEST + (angle != PI);
		return ;
	}
	loop_until_hit_wall(data->map, r);
	r->distance = distance_between_points(pos, r->co);
}

static void	check_vertical(t_data *data, t_raycatsing *r, t_dco pos, \
				double angle)
{
	double	n_tan;

	r->distance = 10000;
	n_tan = -tan(angle);
	if (angle > PI2 && angle < PI3)
	{
		r->co.x = (int)pos.x - 0.0000001;
		r->co.y = (pos.x - r->co.x) * n_tan + pos.y;
		r->step = (t_dco){-1, n_tan};
		r->wall = WEST;
	}
	else if (angle < PI2 || angle > PI3)
	{
		r->co.x = (int)pos.x + 1;
		r->co.y = (pos.x - r->co.x) * n_tan + pos.y;
		r->step = (t_dco){1, -n_tan};
		r->wall = EAST;
	}
	else
	{
		r->co = pos;
		r->wall = NOTHING + (angle == PI3);
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
