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

static void	send_rays(t_data *data);
static void	draw_raycasting(t_data *data, t_dco pos, double angle, int i);
void		init_door(t_data *data, t_raycatsing *r, t_raycatsing *door);
void		init_texture(t_data *data, t_raycatsing *r, t_ico lineh);
void		init_rays(t_raycatsing *r, t_dco pos, int i);
void		check_horizontal(t_data *data, t_raycatsing *r, t_raycatsing *door, \
				double angle);
void		check_vertical(t_data *data, t_raycatsing *r, t_raycatsing *door, \
				double angle);
static void	compute_line_height(t_data *data, t_raycatsing *r, double angle, \
				int i);
void		stop_animation(t_data *data);

void	raycasting(t_data *data)
{
	pthread_t		t[MAX_THREAD];
	int				i;

	data->i = 0;
	if (data->door.is_animation)
	{
		data->door.pos = animation(data->door.start, data->door.end, \
			data->door.i);
		if (data->door.i == 28)
			stop_animation(data);
	}
	i = 0;
	while (i < MAX_THREAD)
		pthread_create(&t[i++], NULL, (void *)send_rays, data);
	i = 0;
	while (i < MAX_THREAD)
		pthread_join(t[i++], NULL);
	if (data->door.is_animation)
		data->door.i += 1;
}

static void	send_rays(t_data *data)
{
	double	angle;
	int		i;

	while (TRUE)
	{
		pthread_mutex_lock(&data->mutex_i);
		i = data->i;
		data->i++;
		pthread_mutex_unlock(&data->mutex_i);
		if (i >= WIDTH)
			break ;
		if (i < HWIDTH)
			angle = HWIDTH - i;
		else
			angle = i - HWIDTH;
		angle = radian_to_degre(atan(angle * data->ratio_horizontal));
		if (i < HWIDTH)
			angle *= -1;
		angle = rotate_degre(data->map->degre + angle);
		draw_raycasting(data, data->map->pos, angle, i);
	}
}

static void	draw_raycasting(t_data *data, t_dco pos, double angle, int i)
{
	t_raycatsing	r[3];

	init_rays(r + DOOR_STATE, pos, i);
	init_rays(r, pos, i);
	check_horizontal(data, r, r + DOOR_STATE, degre_to_radian(angle));
	init_rays(r + VERTICAL, pos, i);
	check_vertical(data, r + VERTICAL, r + DOOR_STATE, degre_to_radian(angle));
	r[HORIZONTAL].co_door = r[DOOR_STATE].co_door;
	r[HORIZONTAL].is_open_door = r[DOOR_STATE].is_open_door;
	r[VERTICAL].co_door = r[DOOR_STATE].co_door;
	r[VERTICAL].is_open_door = r[DOOR_STATE].is_open_door;
	compute_line_height(data, r + (r[VERTICAL].distance < \
		r[HORIZONTAL].distance), angle, i);
}

static void	compute_line_height(t_data *data, t_raycatsing *r, double angle, \
				int i)
{
	int				line_height;
	int				draw_line_height;
	t_wall			w;

	r->distance *= cos(data->map->radian - degre_to_radian(angle));
	line_height = HEIGHT / r->distance;
	if (r->is_active && !r->is_open_door)
		init_door(data, r, NULL);
	if (line_height > HEIGHT)
		draw_line_height = HEIGHT;
	else
		draw_line_height = line_height;
	r->line = (t_dco){i, HHEIGHT - draw_line_height / 2};
	if (r->is_door)
		w = DOOR;
	else
		w = r->wall;
	if (data->map->t[w].is_texture)
		init_texture(data, r, (t_ico){draw_line_height, line_height});
	else
		draw_line(data, r->line, (t_dco){r->line.x, r->line.y + \
			draw_line_height}, data->map->t[w].color);
	data->fov_line[i] = (t_dco){r->co.x, r->co.y};
}
