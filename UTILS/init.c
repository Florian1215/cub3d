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
static void	init_menu(t_data *data);
void		init_fov(t_data *data, int right_pan);
void		init_lvl(t_data *data);
void		load_textures(t_data *data);

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
	load_textures(data);
}

static void	init_imgs(t_data *data)
{
	init_img(&data->img, NULL, data->mlx_ptr);
	init_img(&data->logo, PATH_LOGO, data->mlx_ptr);
	init_img(&data->fovs[0], PATH_70, data->mlx_ptr);
	init_img(&data->fovs[1], PATH_90, data->mlx_ptr);
	init_img(&data->fovs[2], PATH_110, data->mlx_ptr);
	init_img(&data->fovs[3], PATH_FOV, data->mlx_ptr);
	init_img(&data->lvls[0], PATH_EASY, data->mlx_ptr);
	init_img(&data->lvls[1], PATH_NORMAL, data->mlx_ptr);
	init_img(&data->lvls[2], PATH_HARD, data->mlx_ptr);
	init_img(&data->lvls[3], PATH_LVL, data->mlx_ptr);
}

void	init_img(t_img *img, char *path, void *mlx_ptr)
{
	if (path)
		img->img = mlx_xpm_file_to_image(mlx_ptr, path, \
			&img->width, &img->height);
	else
		img->img = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img)
		return ;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	img->bit_ratio = img->bits_per_pixel / 8;
}

static void	init_menu(t_data *data)
{
	const int	size = MINIMAP_SIZE + MINIMAP_OFFSET;
	const int	offset = (WIN_HEIGHT - (size * 2)) / 3;
	const int	right_pan = (size + offset) * 2 + offset + 5;
	t_menus		i;

	data->size_edit = (t_ico){WIDTH_EDIT, HEIGHT_EDIT};
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
	data->menu[LOGO].pos.y = PADY_LOGO;
	init_fov(data, right_pan);
	init_lvl(data);
}
