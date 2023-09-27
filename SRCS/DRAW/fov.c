/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/08/29 13:46:10 by mfinette         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_fov_line(t_data *data);

// TODO fix data race

void	draw_fov(t_data	*data, t_ico offset)
{
	pthread_t		t[MAX_THREAD];
	int				i;

	data->i = 0;
	i = 0;
	data->map->omap_menu = offset;
	while (i < MAX_THREAD)
	{
		if (pthread_create(&t[i++], NULL, \
		(void *)draw_fov_line, data) != SUCCESS)
			close_mlx(data);
	}
	i = 0;
	while (i < MAX_THREAD)
		pthread_join(t[i++], NULL);
}

static void	draw_fov_line(t_data *data)
{
	int	i;

	while (TRUE)
	{
		pthread_mutex_lock(&data->mutex_i);
		i = data->i;
		data->i++;
		pthread_mutex_unlock(&data->mutex_i);
		if (i >= WIDTH)
			break ;
		draw_line(data, get_map_dco(data->map, data->map->omap_menu), (t_dco) \
		{data->fov_line[i].x * data->map->square_size + data->map->omap_menu.x, \
		data->fov_line[i].y * data->map->square_size + data->map->omap_menu.y}, \
		FOV_COLOR);
	}
}

void	init_ratio(t_data *data)
{
	const double	fovs[3] = {76.62, 76.96, 89.885};

	data->ratio_horizontal = 2 * tan(fovs[data->fov.s - FOV_70] / 2) / WIDTH;
}
