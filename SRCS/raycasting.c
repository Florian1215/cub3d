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

void		load_texture(t_data *data);
static void	send_rays(t_data *data);
void		init_rays(t_data *data, t_raycatsing *r, t_dco ray_dir, \
				int i);
void		loop_until_hit_wall(t_data *data, t_raycatsing *r);
void		init_door(t_data *data, t_raycatsing *r, t_bool is_open_door);
void		init_texture(t_data *data, t_raycatsing *r, t_ico lineh);
static void	draw_raycasting(t_data *data, t_raycatsing *r, int i);

void	raycasting(t_data *data)
{
	pthread_t		t[MAX_THREAD];
	int				i;

	update_direction(data);
	data->i = 0;
	if (!data->map->is_load_texture)
		load_texture(data);
	if (data->door.is_animation)
	{
		data->door.pos = animation(data->door.start, data->door.end, \
			data->door.i);
		if (data->door.i == 28)
			stop_door_animation(data);
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
	int				i;
	t_raycatsing	r;
	double			camera_x;

	while (TRUE)
	{
		pthread_mutex_lock(&data->mutex_i);
		i = data->i;
		data->i++;
		pthread_mutex_unlock(&data->mutex_i);
		if (i >= WIDTH)
			break ;
		camera_x = data->fov_value.y * (float)i / WIDTH - 1;
		init_rays(data, &r, dco_add(data->map->direction, \
dco_mul(data->map->fov, camera_x)), i);
		loop_until_hit_wall(data, &r);
		draw_raycasting(data, &r, i);
	}
}

static void	draw_raycasting(t_data *data, t_raycatsing *r, int i)
{
	int		line_height;
	int		draw_line_height;
	t_wall	w;

	line_height = HEIGHT / r->distance;
	if (r->is_active && !r->is_open_door)
		init_door(data, r, FALSE);
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
	data->fov_line[i] = r->co;
	data->sprite_distance[i] = r->distance;
}
