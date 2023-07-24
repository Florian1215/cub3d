/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:50:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 19:03:26 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_distance(t_data *data);

void	init_data(t_data *data)
{
	data->is_menu = FALSE;
	data->is_menu_animation = FALSE;
	data->is_launch_animation = FALSE;
	data->is_menu = FALSE;
	data->map = NULL;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
		WIN_WIDTH, WIN_HEIGHT, "cub3d du bde c la follie");
	data->img.img = mlx_new_image(data->mlx_ptr, \
		WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, \
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	data->key_arrow_press[LEFT] = FALSE;
	data->key_arrow_press[UP] = FALSE;
	data->key_arrow_press[RIGHT] = FALSE;
	data->key_arrow_press[DOWN] = FALSE;
	data->offset_minimap = (t_ico){MINIMAP_OFFSET, MINIMAP_OFFSET};
	init_distance(data);
}

static void	init_distance(t_data *data)
{
	data->distances.distance = NULL;
	data->distances.angle = NULL;
	data->distances.face = NULL;
	data->distances.size = (int)(FOV / DEFINITION);
	data->distances.distance = malloc(sizeof(double) * data->distances.size);
	if (!data->distances.distance)
		exit(ERROR_MALLOC);
	data->distances.angle = malloc(sizeof(double) * data->distances.size);
	if (!data->distances.angle)
		exit(ERROR_MALLOC);
	data->distances.face = malloc(sizeof(int) * data->distances.size);
	if (!data->distances.face)
		exit(ERROR_MALLOC);
}

t_exit	init_map(t_map *map)
{
	int	k;

	map->height = lst_size(map->lst);
	map->m = malloc(sizeof(t_map *) * map->height);
	if (!map->m)
		return (ERROR_MALLOC);
	map->width = lst_max_len(map->lst);
	k = 0;
	map->square_size = MINIMAP_SIZE / fmax(map->height, map->width);
	map->hitbox = map->square_size / 2;
	if (map->hitbox < 4)
		map->hitbox = 4;
	map->hhitbox = map->hitbox / 2;
	map->qhitbox = map->hhitbox / 2;
	while (k < map->height)
	{
		map->m[k] = malloc(sizeof(t_map) * map->width);
		if (!map->m[k])
			return (free_n_split((void **)map->m, k - 1), ERROR_MALLOC);
		k++;
	}
	return (SUCCESS);
}
