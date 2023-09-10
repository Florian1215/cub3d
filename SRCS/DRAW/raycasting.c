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

static void	raycasting_thread(t_data *data);
static void	draw_raycasting(t_data *data, t_dco pos, double angle, int i);
void		draw_texture(t_data *data, t_raycatsing *r, int dlineh, int lineh);
void		check_horizontal(t_data *data, t_raycatsing *r, t_dco pos, \
				double angle);
void		check_vertical(t_data *data, t_raycatsing *r, t_dco pos, \
				double angle);

void	raycasting(t_data *data)
{
	pthread_t		t[MAX_THREAD];
	int				i;

	data->raycast_i = 0;
	i = 0;
	while (i < MAX_THREAD)
		pthread_create(&t[i++], NULL, (void *)raycasting_thread, data);
	i = 0;
	while (i < MAX_THREAD)
		pthread_join(t[i++], NULL);
}

static void	raycasting_thread(t_data *data)
{
	double	angle;
	int		i;

	pthread_mutex_lock(&data->mutex_i);
	i = data->raycast_i;
	data->raycast_i++;
	pthread_mutex_unlock(&data->mutex_i);
	if (i >= WIN_WIDTH)
		return ;
	if (i < HWIN_WIDTH)
		angle = HWIN_WIDTH - i;
	else
		angle = i - HWIN_WIDTH;
	angle = radian_to_degre(atan(angle * data->ratio_horizontal));
	if (i < HWIN_WIDTH)
		angle *= -1;
	angle = rotate_degre(data->map->degre + angle);
	draw_raycasting(data, data->map->pos, angle, i);
	raycasting_thread(data);
}

static void	draw_raycasting(t_data *data, t_dco pos, double angle, int i)
{
	t_raycatsing	r[2];
	int				m;
	int				line_height;
	int				draw_line_height;

	r[0].distance = 10000;
	check_horizontal(data, r, pos, degre_to_radian(angle));
	r[1].distance = 10000;
	check_vertical(data, r + 1, pos, degre_to_radian(angle));
	m = (r[0].distance > r[1].distance);
	r[m].distance *= cos(data->map->radian - degre_to_radian(angle));
	line_height = WIN_HEIGHT / r[m].distance;
	if (line_height > WIN_HEIGHT)
		draw_line_height = WIN_HEIGHT;
	else
		draw_line_height = line_height;
	r[m].line = (t_dco){i, HWIN_HEIGHT - draw_line_height / 2};
	if (data->map->t[r->wall].is_texture)
		draw_texture(data, r + m, draw_line_height, line_height);
	else
		draw_line(data, r[m].line, (t_dco){r[m].line.x, r[m].line.y + \
			draw_line_height}, data->map->t[r[m].wall].color);
	data->fov_line[i] = (t_dco){r[m].co.x + (r[m].step.x / data->map-> \
		square_size), r[m].co.y + (r[m].step.y / data->map->square_size)};
}
