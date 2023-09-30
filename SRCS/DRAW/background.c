/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:47:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/16 17:47:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background_line(t_data *data);

void	draw_background(t_data *data)
{
	pthread_t		t[MAX_THREAD];
	int				i;

	data->i = 0;
	i = 0;
	while (i < MAX_THREAD)
		pthread_create(&t[i++], NULL, (void *)draw_background_line, data);
	i = 0;
	while (i < MAX_THREAD)
		pthread_join(t[i++], NULL);
}

static void	draw_background_line(t_data *data)
{
	t_ico	i;

	while (TRUE)
	{
		pthread_mutex_lock(&data->mutex_i);
		i.x = data->i;
		data->i++;
		pthread_mutex_unlock(&data->mutex_i);
		if (i.x >= WIDTH)
			break ;
		i.y = 0;
		while (i.y < HEIGHT)
		{
			mlx_pixel_put_img(&data->img, i.x, i.y, \
				data->map->color[i.y > HHEIGHT]);
			i.y++;
		}
		i.x++;
	}
}
