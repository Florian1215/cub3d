/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:10:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/10/01 19:20:50 by fguirama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO add sprite

static void			init_projection(t_data *data, t_sprite *s, t_dco *fov);
static t_draw_param	get_draw_param(t_data *data, t_dco camera);
void				draw_sprite(t_data *data, t_draw_param dp, const double dist);
static void			draw_stripe(t_data *data, t_draw_param dp);


void	draw_sprites(t_data *data)
{
	t_dco			fov;
	t_sprite		*s;
	t_draw_param	draw_param;

	s = data->map->s;
	while (s)
	{
		if (!s->is_collected)
		{
			if (distance_between_points(data->map->pos, s->co) < \
					data->map->hhitbox)
				s->is_collected = TRUE;
			else
			{
				s->rel_pos.x = data->map->pos.x - s->co.x;
				s->rel_pos.y = data->map->pos.y - s->co.y;
				init_projection(data, s, &fov);
				if (fov.y > 0)
				{
					draw_param = get_draw_param(data, fov);
					draw_sprite(data, draw_param, fov.y);
				}
			}

		}
		s = s->next;
	}
}

static void	init_projection(t_data *data, t_sprite *s, t_dco *fov)
{
	double	inverse_det;


	inverse_det = -1 / (data->map->fov.x * data->map->direction.y - data->map->direction.x * data->map->fov.y);
	fov->x = inverse_det * (data->map->direction.y * s->rel_pos.x - data->map->direction.x * s->rel_pos.y);
	fov->y = inverse_det * (-data->map->fov.y * s->rel_pos.x + data->map->fov.x * s->rel_pos.y);
}

static t_draw_param	get_draw_param(t_data *data, t_dco camera)
{
	t_draw_param	dp;
	int				scale;

	dp.sprite = &data->sprite_img;
	dp.width = SIZE_SPRITE / camera.y;
	dp.height = ((double)dp.sprite->height / dp.sprite->width) * SIZE_SPRITE / camera.y;
	dp.screen.x = (WIDTH / 2.f) * (1 + camera.x / camera.y);
	dp.draw_start.x = dp.screen.x - dp.width / 2;
	dp.draw_end.x = dp.screen.x + dp.width / 2;
	scale = abs((int)(HEIGHT / camera.y / 2));
	dp.draw_start.y = HEIGHT / 2 + scale - dp.height;
	dp.draw_end.y = HEIGHT / 2 + scale;
	return (dp);
}

void	draw_sprite(t_data *data, t_draw_param dp, const double dist)
{
	dp.screen.x = dp.draw_start.x;
	if (dp.screen.x < 0)
		dp.screen.x = 0;
	while (dp.screen.x < dp.draw_end.x && dp.screen.x < WIDTH)
	{
		if (dp.screen.x < WIDTH && dp.screen.x >= 0 && data->sprite_distance[dp.screen.x] > dist)
		{
			dp.texture.x = (dp.screen.x - dp.draw_start.x) * dp.sprite->width / dp.width;
			draw_stripe(data, dp);
		}
		dp.screen.x++;
	}
}

static void	draw_stripe(t_data *data, t_draw_param dp)
{
	dp.screen.y = dp.draw_start.y;
	if (dp.screen.y < 0)
		dp.screen.y = 0;
	while (dp.screen.y < dp.draw_end.y && dp.screen.y < HEIGHT)
	{
		dp.texture.y = (dp.screen.y - dp.draw_start.y) * dp.sprite->height / dp.height;
		dp.color = *(int *)(dp.sprite->addr + dp.texture.x * dp.sprite->bit_ratio + dp.texture.y * dp.sprite->line_length);
		if (!(dp.color & 0xFF000000))
			mlx_pixel_put_img(&data->img, dp.screen.x, dp.screen.y, dp.color);
		dp.screen.y++;
	}
}

void	draw_sprites_minimap(t_data *data, t_ico offset)
{
	t_sprite	*s;
	double		d;
	t_ico		co;

	d = (data->map->hhitbox / 1.5);
	s = data->map->s;
	while (s)
	{
		if (!s->is_collected)
		{
			co.x = (int)((s->co.x - (d / 2)) * \
			data->map->square_size + offset.x);
			co.y = (int)((s->co.y - (d / 2)) * \
			data->map->square_size + offset.y);
			draw_circle((t_draw){&data->img, SPRITE_COLOR, \
			(int)(d * data->map->square_size)}, co);
		}
		s = s->next;
	}
}
