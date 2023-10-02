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
// TODO can collect

static t_dco		camera_projection(t_data *data, t_sprite *collectible);
static t_draw_param	get_draw_param(t_data *data, t_dco camera);
void				draw_sprite(t_data *data, t_draw_param dp, const float dist);


void	draw_sprites(t_data *data)
{
	t_sprite		*s;
	t_draw_param	draw_param;
	t_dco			camera;

	s = data->map->s;
	while (s)
	{
		s->rel_pos = (t_dco){data->map->pos.x - s->co.x, data->map->pos.y - s->co.y};
		camera = camera_projection(data, s);
		if (camera.y > 0)
		{
			draw_param = get_draw_param(data, camera);
			draw_sprite(data, draw_param, camera.y);
		}
		s = s->next;
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

static void	draw_stripe(t_data *data, t_draw_param dp)
{
	dp.screen.y = dp.draw_start.y;
	if (dp.screen.y < 0)
		dp.screen.y = 0;
//	printf("%d - %d\n", dp.screen.y, dp.draw_end.y);
	while (dp.screen.y < dp.draw_end.y && dp.screen.y < HEIGHT)
	{
		dp.texture.y = (dp.screen.y - dp.draw_start.y) * dp.sprite->height / dp.height;
		dp.color = *(int *)(dp.sprite->addr + dp.texture.x * dp.sprite->bit_ratio + dp.texture.y * dp.sprite->line_length);
		if (!(dp.color & 0xFF000000))
		{
			mlx_pixel_put_img(&data->img, dp.screen.x, dp.screen.y, dp.color);
//			printf("draw srpte\n");
		}
		dp.screen.y++;
	}
}

void	draw_sprite(t_data *data, t_draw_param dp, const float dist)
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

static t_draw_param	get_draw_param(t_data *data, t_dco camera)
{
	t_draw_param	dp;
	int				scale;

	dp.sprite = &data->sprite_img;
	dp.width = 200.f / camera.y;
	dp.height = ((double)dp.sprite->height / dp.sprite->width) * 200.f / camera.y;
	dp.screen.x = (WIDTH / 2.f) * (1 + camera.x / camera.y);
	dp.draw_start.x = dp.screen.x - dp.width / 2;
	dp.draw_end.x = dp.screen.x + dp.width / 2;
	scale = abs((int)(HEIGHT / camera.y / 2));
	dp.draw_start.y = HEIGHT / 2 + scale - dp.height;
	dp.draw_end.y = HEIGHT / 2 + scale;
//	printf("%d %d %d | %d - %d\n", dp.height, dp.sprite->height, dp.sprite->width, dp.draw_start.y, dp.draw_end.y);
	return (dp);
}

static t_dco	camera_projection(t_data *data, t_sprite *collectible)
{
	t_dco	camera;
	float	inverse_det;

	inverse_det = -1.f / (
			data->map->camera.x * data->map->direction.y
			- data->map->direction.x * data->map->camera.y);
	camera.x = inverse_det * (
			data->map->direction.y * collectible->rel_pos.x
			- data->map->direction.x * collectible->rel_pos.y);
	camera.y = inverse_det * (
			-data->map->camera.y * collectible->rel_pos.x
			+ data->map->camera.x * collectible->rel_pos.y);
	return (camera);
}

