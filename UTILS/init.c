/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:11:45 by fguirama          #+#    #+#             */
/*   Updated: 2023/09/20 17:11:45 by fguirama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void		init_fov(t_data *data, int rpan);
void		init_lvl(t_data *data);
void		load_textures(t_data *data);

void	init_data(t_data *data)
{
	int	i;

	data->hover = POS_ERROR;
	data->launch_animation = FALSE;
	data->mouse_press = FALSE;
	data->door.is_animation = FALSE;
	data->door.is_scope = FALSE;
	data->door.is_opening = FALSE;
	data->n_map = map_size(data->map);
	if (data->n_map > 4)
		data->n_map = 4;
	data->txt_pos.x = WIDTH / 2 - 76;
	data->txt_pos.y = HEIGHT / 2 - 15;
	data->v_pos.x = WIDTH / 2 - SIZE_V / 2;
	data->v_pos.y = HEIGHT / 2 - SIZE_V / 2;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, TITLE);
	init_imgs(data);
	i = 0;
	while (i < KEYPRESS)
		data->keypress[i++] = FALSE;
	init_menu(data);
	init_ratio(data);
	load_textures(data);
	pthread_mutex_init(&data->mutex_i, NULL);
}

static void	init_imgs(t_data *data)
{
	init_img(&data->img, NULL, data->mlx_ptr);
	init_img(&data->logo, PATH_LOGO, data->mlx_ptr);
	init_img(&data->fov.imgs[0], PATH_70, data->mlx_ptr);
	init_img(&data->fov.imgs[1], PATH_90, data->mlx_ptr);
	init_img(&data->fov.imgs[2], PATH_110, data->mlx_ptr);
	init_img(&data->fov.imgs[3], PATH_FOV, data->mlx_ptr);
	init_img(&data->lvl.imgs[0], PATH_EASY, data->mlx_ptr);
	init_img(&data->lvl.imgs[1], PATH_NORMAL, data->mlx_ptr);
	init_img(&data->lvl.imgs[2], PATH_HARD, data->mlx_ptr);
	init_img(&data->lvl.imgs[3], PATH_LVL, data->mlx_ptr);
	init_img(&data->sprite_img, PATH_COINS, data->mlx_ptr);
}

void	init_img(t_img *img, char *path, void *mlx_ptr)
{
	if (path)
		img->img = mlx_xpm_file_to_image(mlx_ptr, path, \
			&img->width, &img->height);
	else
		img->img = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	if (!img->img)
		return ;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	img->bit_ratio = img->bits_per_pixel / 8;
}

static void	init_menu(t_data *data)
{
	const int	size = MINIMAP_SIZE + MINIMAP_OFFSET;
	const int	offset = (HEIGHT - (size * 2)) / 3;
	const int	right_pan = (size + offset) * 2;
	const int	offset_x = right_pan + ((WIDTH - right_pan) / 2);
	t_menus		i;

	data->size_slider = (t_ico){WIDTH_EDIT, HEIGHT_EDIT};
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
	data->menu[LOGO].pos.x = offset_x - ((data->logo.width * RLOGO) / 2);
	data->menu[LOGO].pos.y = (offset / 2) + (HEIGHT / 4) - \
		((data->logo.height * RLOGO) / 2);
	init_fov(data, offset_x);
	init_lvl(data);
}
