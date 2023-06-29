/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:27:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/06 20:27:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void			compute_map_offset(t_data *data);
static void		draw_rounded_squares(t_data *data);
static void		set_minimap(t_data *data);
void			set_minimap_animation(t_data *data);
void			change_n_map(t_data *data, int n);

void	handle_menu(t_data *data)
{
	if (!data->is_menu)
	{
		compute_map_offset(data);
		data->is_menu_animation = TRUE;
	}
	else
	{
		data->is_launch_animation = TRUE;
		data->is_menu = FALSE;
	}
}

void	set_menu(t_data *data)
{
	data->is_menu = TRUE;
	draw_square(&data->img, (t_ico){0, 0}, WIN_WIDTH, 0x46458C);
	draw_rounded_squares(data);
	if (data->is_menu_animation)
		set_minimap_animation(data);
	else
		set_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}

static void	draw_rounded_squares(t_data *data)
{
	int			i;
	const int	size = MINIMAP_SIZE + MINIMAP_OFFSET;
	t_ico		offset_square;

	i = 0;
	while (i < 4)
	{
		offset_square.x = (i % 2) * (MINIMAP_OFFSET * 2 + size);
		offset_square.y = (i > 1) * (MINIMAP_OFFSET * 2 + size);
		draw_round_square(&data->img, (t_ico){MINIMAP_OFFSET + offset_square.x, \
			MINIMAP_OFFSET + offset_square.y}, size, 20, 0xC2DEDC);
		i++;
	}
}

static void	set_minimap(t_data *data)
{
	int		i;
	t_map	*map;

	compute_map_offset(data);
	i = 0;
	map = data->map;
	while (i < 4 && map)
	{
		print_minimap(data, map, map->offset_map_menu);
		print_player(data, map, map->offset_map_menu);
		map = map->next;
		i++;
	}
}

void	select_map(t_data *data, t_ico click)
{
	int			i;
	const int	size = MINIMAP_SIZE + MINIMAP_OFFSET;
	t_map		*map;
	t_ico		offset_square;

	i = 0;
	map = data->map;
	while (i < 4 && map)
	{
		offset_square.x = (i % 2) * (MINIMAP_OFFSET * 2 + size);
		offset_square.y = (i > 1) * (MINIMAP_OFFSET * 2 + size);
		if (click.x >= (MINIMAP_OFFSET + offset_square.x) && \
			click.x <= (MINIMAP_OFFSET + offset_square.x + size) && \
			click.y >= (MINIMAP_OFFSET + offset_square.y) && \
			click.y <= (MINIMAP_OFFSET + offset_square.y + size))
		{
			change_n_map(data, i);
			data->is_launch_animation = TRUE;
			data->is_menu = FALSE;
			return ;
		}
		map = map->next;
		i++;
	}
}
