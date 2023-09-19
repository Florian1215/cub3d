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
void		draw_texture(t_data *data, t_raycatsing *r, int dlineh, int lineh);
void		check_horizontal(t_data *data, t_raycatsing *r, t_dco pos, \
				double angle);
void		check_vertical(t_data *data, t_raycatsing *r, t_dco pos, \
				double angle);
static void	comput_line_height(t_data *data, t_raycatsing *r, double angle, \
				int i);

void	raycasting(t_data *data)
{
	pthread_t		t[MAX_THREAD];
	int				i;

	data->raycast_i = 0;
	i = 0;
	while (i < MAX_THREAD)
	{
		if (pthread_create(&t[i++], NULL, (void *)send_rays, data) != SUCCESS)
			close_mlx(data);
	}
	i = 0;
	while (i < MAX_THREAD)
		pthread_join(t[i++], NULL);
	if (data->door.is_animation)
		data->door.i += 2;
}

static void	send_rays(t_data *data)
{
	double	angle;
	int		i;

	pthread_mutex_lock(&data->mutex_i);
	i = data->raycast_i;
	data->raycast_i++;
	pthread_mutex_unlock(&data->mutex_i);
	if (i >= WIDTH)
		return ;
	if (i < HWIDTH)
		angle = HWIDTH - i;
	else
		angle = i - HWIDTH;
	angle = radian_to_degre(atan(angle * data->ratio_horizontal));
	if (i < HWIDTH)
		angle *= -1;
	angle = rotate_degre(data->map->degre + angle);
	draw_raycasting(data, data->map->pos, angle, i);
	send_rays(data);
}

static void	draw_raycasting(t_data *data, t_dco pos, double angle, int i)
{
	t_raycatsing	r[2];

	r[0].is_active = i == WIDTH / 2;
	r[0].distance = 10000;
	check_horizontal(data, r, pos, degre_to_radian(angle));
	r[1].is_active = i == WIDTH / 2;
	r[1].distance = 10000;
	check_vertical(data, r + 1, pos, degre_to_radian(angle));
	r[0].is_open_door = r[0].is_open_door || r[1].is_open_door;
	r[1].is_open_door = r[0].is_open_door;
	comput_line_height(data, r + (r[1].distance < r[0].distance), angle, i);
}

static void	comput_line_height(t_data *data, t_raycatsing *r, double angle, \
				int i)
{
	int				line_height;
	int				draw_line_height;

	r->distance *= cos(data->map->radian - degre_to_radian(angle));
	line_height = HEIGHT / r->distance;
	if (r->is_active && !r->is_open_door && !data->door.is_animation)
	{
		data->door.is_scope = r->wall == DOOR && r->distance < 2;
		data->door.co = (t_ico){r->co.x, r->co.y};
		data->door.is_opening = FALSE;
	}
	if (line_height > HEIGHT)
		draw_line_height = HEIGHT;
	else
		draw_line_height = line_height;
	r->line = (t_dco){i, HHEIGHT - draw_line_height / 2};
	if (data->map->t[r->wall].is_texture)
		draw_texture(data, r, draw_line_height, line_height);
	else
		draw_line(data, r->line, (t_dco){r->line.x, r->line.y + \
			draw_line_height}, data->map->t[r->wall].color);
	data->fov_line[i] = (t_dco){r->co.x, r->co.y};
}
