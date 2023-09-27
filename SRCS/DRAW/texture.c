/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:24:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/08/30 18:24:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_band(t_data *data, t_ray ray, t_draw_param dp);
static void	mlx_get_wall_stripe(int *stripe, t_draw_param dp);
static void	mlx_put_wall_stripe(t_data *data, const int *stripe, t_draw_param dp);

void	draw_wall(t_data *data, int screen_x, t_ray ray)
{
	t_draw_param	dp;

	dp.screen.x = screen_x;
	dp.height = HEIGHT / ray.length;
	dp.draw_start.y = HEIGHT / 2 - dp.height / 2;
	dp.draw_end.y = HEIGHT / 2 + dp.height / 2;
	draw_wall_band(data, ray, dp);
}

static void	draw_wall_band(t_data *data, t_ray ray, t_draw_param dp)
{
	int			stripe[HEIGHT];

	if (ray.is_door)
		dp.sprite = data->map->t[DOOR].img;
	else
		dp.sprite = data->map->t[ray.wall_face].img;
	if (ray.wall_face == NORTH || ray.wall_face == SOUTH)
		dp.texture.x = (ray.pos.x - (int) ray.pos.x) * dp.sprite.width;
	else
		dp.texture.x = (ray.pos.y - (int) ray.pos.y) * dp.sprite.width;
	dp.screen.y = dp.draw_start.y;
	if (dp.screen.y < 0)
		dp.screen.y = 0;
	mlx_get_wall_stripe(stripe, dp);
	mlx_put_wall_stripe(data, stripe, dp);
}

static void	mlx_get_wall_stripe(int *stripe, t_draw_param dp)
{
	char	*texture_addr;
	float	step;
	int		i;

	step = (float) dp.sprite.height / dp.height;
	texture_addr = dp.sprite.addr
				   + dp.texture.x * dp.sprite.bit_ratio;
	i = 0;
	while (dp.screen.y < dp.draw_end.y && dp.screen.y < HEIGHT)
	{
		dp.texture.y = (dp.screen.y - dp.draw_start.y) * step;
		stripe[i] = *(int *)(texture_addr
							 + dp.texture.y * dp.sprite.line_length);
		dp.screen.y++;
		i++;
	}
}

static void	mlx_put_wall_stripe(t_data *data, const int *stripe, t_draw_param dp)
{
	char	*img_addr;
	int		i;

	if (dp.draw_end.y > HEIGHT)
		dp.draw_end.y = HEIGHT;
	img_addr = data->img.addr;
	img_addr += dp.screen.x * data->img.bit_ratio;
	img_addr += dp.screen.y * data->img.line_length;
	i = 0;
	while (dp.screen.y + i < dp.draw_end.y)
	{
		*(int *)img_addr = stripe[i];
		img_addr += data->img.line_length;
		i++;
	}
}

void	load_textures(t_data *data)
{
	const int	colors[5] = {NORTH_COLOR, SOUTH_COLOR, WEST_COLOR, EAST_COLOR, \
							DOOR_CLOSE_COLOR};
	t_map		*m;
	t_wall		s;

	m = data->map;
	while (m)
	{
		s = NORTH;
		while (s <= DOOR)
		{
			if (m->t[s].path)
				init_img(&m->t[s].img, m->t[s].path, data->mlx_ptr);
			m->t[s].color = colors[s];
			m->t[s].is_texture = m->t[s].path && m->t[s].img.img;
			s++;
		}
		m = m->next;
	}
}
