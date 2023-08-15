/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:50:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 19:03:26 by mfinette         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_imgs(t_data *data);
static void	init_img(t_data *data, t_img *img, char *path);
static void	init_menu(t_data *data);
void		init_fov(t_data *data, int right_pan);
void		init_lvl(t_data *data);
static void	init_distance(t_data *data);

void	init_data(t_data *data)
{
	int	i;

	data->hover = POS_ERROR;
	data->launch_animation = FALSE;
	data->mouse_press = FALSE;
	data->n_map = map_size(data->map);
	if (data->n_map > 4)
		data->n_map = 4;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, TITLE);
	init_imgs(data);
	i = 0;
	while (i < KEYPRESS)
		data->key_arrow_press[i++] = FALSE;
	init_menu(data);
	init_distance(data);
}

static void	init_imgs(t_data *data)
{
	init_img(data, &data->img, NULL);
	init_img(data, &data->logo, PATH_LOGO);
	init_img(data, &data->fovs[0], PATH_70);
	init_img(data, &data->fovs[1], PATH_90);
	init_img(data, &data->fovs[2], PATH_110);
	init_img(data, &data->fovs[3], PATH_FOV);
	init_img(data, &data->lvls[0], PATH_EASY);
	init_img(data, &data->lvls[1], PATH_NORMAL);
	init_img(data, &data->lvls[2], PATH_HARD);
	init_img(data, &data->lvls[3], PATH_LVL);
}

static void	init_img(t_data *data, t_img *img, char *path)
{
	if (path)
		img->img = mlx_xpm_file_to_image(data->mlx_ptr, path, \
			&img->width, &img->height);
	else
		img->img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	img->bit_ratio = img->bits_per_pixel / 8;
}

static void	init_menu(t_data *data)
{
	const int	size = MINIMAP_SIZE + MINIMAP_OFFSET;
	const int	offset = (WIN_HEIGHT - (size * 2)) / 3;
	const int	right_pan = (size + offset) * 2 + offset + 5;
	t_pos		i;

	data->size_edit = (t_ico){100, 60};
	data->in_menu = FALSE;
	data->menu_animation = FALSE;
	data->hover_animation = FALSE;
	i = POS_1;
	while (i < 4)
	{
		data->menu[i].pos.x = ((i % 2) * (size + offset)) + offset;
		data->menu[i].pos.y = ((i > 1) * (size + offset)) + offset;
		data->menu[i].size = (t_ico){size, size};
		i++;
	}
	data->menu[LOGO].pos.x = right_pan;
	data->menu[LOGO].pos.y = 110;
	init_fov(data, right_pan);
	init_lvl(data);
}

static void	init_distance(t_data *data)
{
	data->distances.distance = NULL;
	data->distances.angle = NULL;
	data->distances.face = NULL;
	data->distances.size = (int)(90 / DEFINITION);
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
