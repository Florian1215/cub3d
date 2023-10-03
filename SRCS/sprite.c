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

static void			init_projection(t_data *data, t_sprite *s, t_dco *fov);
static void			draw_sprite(t_data *data, t_sprite *s, t_dco fov);
static void			init_draw_sprite(t_data *data, t_sprite *s, t_dco fov);
static void			draw_line_x(t_data *data, t_sprite *s);

void	draw_sprites(t_data *data)
{
	t_dco			fov;
	t_sprite		*s;

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
					draw_sprite(data, s, fov);
			}

		}
		s = s->next;
	}
}

static void	init_projection(t_data *data, t_sprite *s, t_dco *fov)
{
	double	inverse_det;


	inverse_det = -1.0 / (data->map->fov.x * data->map->direction.y - \
data->map->direction.x * data->map->fov.y);
	fov->x = inverse_det * (data->map->direction.y * s->rel_pos.x - \
data->map->direction.x * s->rel_pos.y);
	fov->y = inverse_det * (-data->map->fov.y * s->rel_pos.x + \
data->map->fov.x * s->rel_pos.y);
}

static void	draw_sprite(t_data *data, t_sprite *s, t_dco fov)
{
	init_draw_sprite(data, s, fov);
	s->screen.x = s->start.x;
	if (s->screen.x < 0)
		s->screen.x = 0;
	while (s->screen.x < s->end.x && s->screen.x < WIDTH)
	{
		if (s->screen.x < WIDTH && s->screen.x >= 0 && \
				data->sprite_distance[s->screen.x] > fov.y)
			draw_line_x(data, s);
		s->screen.x++;
	}
}

static void	init_draw_sprite(t_data *data, t_sprite *s, t_dco fov)
{
	int				scale;

	s->size.x = SIZE_SPRITE / fov.y;
	s->size.y = ((double)data->sprite_img.height / data->sprite_img.width) * \
SIZE_SPRITE / fov.y;
	s->screen.x = (WIDTH / data->fov_value.y) * (1 + fov.x / fov.y);
	s->start.x = s->screen.x - s->size.x / 2;
	s->end.x = s->screen.x + s->size.x / 2;
	scale = abs((int)(HEIGHT / fov.y / 2));
	s->start.y = HEIGHT / 2 + scale - s->size.y;
	s->end.y = HEIGHT / 2 + scale;
}

static void	draw_line_x(t_data *data, t_sprite *s)
{
	int	color;

	s->texture.x = (s->screen.x - s->start.x) * data->sprite_img.width / \
s->size.x;
	s->screen.y = s->start.y;
	if (s->screen.y < 0)
		s->screen.y = 0;
	while (s->screen.y < s->end.y && s->screen.y < HEIGHT)
	{
		s->texture.y = (s->screen.y - s->start.y) * data->sprite_img.height / \
s->size.y;
		color = *(int *)(data->sprite_img.addr + s->texture.x * \
data->sprite_img.bit_ratio + s->texture.y * data->sprite_img.line_length);
		if (!(color & 0xFF000000))
			mlx_pixel_put_img(&data->img, s->screen.x, s->screen.y, color);
		s->screen.y++;
	}
}
