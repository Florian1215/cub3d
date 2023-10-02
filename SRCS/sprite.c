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

double dot_product(t_dco p1, t_dco p2)
{
	return (p1.x * p2.x + p1.y * p2.y);
}

static t_bool	is_sprite_in_fov(t_data *data, t_sprite *sprite, double hfov)
{
	double	toSpriteLength;

	sprite->direction.x = sprite->co.x - data->map->pos.x;
	sprite->direction.y = sprite->co.y - data->map->pos.y;
	toSpriteLength = vector_length(sprite->direction);
	sprite->direction.x /= toSpriteLength;
	sprite->direction.y /= toSpriteLength;
//	printf("%f - %f | %f - %f\n", sprite->direction.x, sprite->direction.y, data->map->direction.x, data->map->direction.y);
	double angle = acos(dot_product(data->map->direction, sprite->direction));
	angle = radian_to_degre(angle);
	if (angle > hfov)
		return (FALSE);
	return (TRUE);
}

t_bool	is_equal_angle(t_dco a1, t_dco a2);

void	add_sprites_in_rays(t_data *data, t_raycatsing *r, int x)
{
	t_sprite	*s;

	s = data->map->s;
	while (s)
	{
		if (!s->is_collected && s->is_in_fov && s->distance < r->distance)
		{
			if (point_belongs_to_line(data->map->pos, r->co, s->co))
			{
				r->is_sprite = TRUE;
				r->sprite_distance = s->distance;
				s->x = x;
			}
		}
		s = s->next;
	}
}

void	add_sprites_in_fov(t_data *data)
{
	t_sprite	*s;

	s = data->map->s;
	while (s)
	{
		if (!s->is_collected)
		{
			s->is_in_fov = is_sprite_in_fov(data, s, 90.0 / 2);
			if (s->is_in_fov)
			{
//				if (i == 0)
//					printf("Angle %f | %f\n", s->angle, data->map->degre);
				s->distance = distance_between_points(\
data->map->pos, s->co);
				if (s->distance < 0.2)
					s->is_collected = TRUE;
			}
			else
				s->x = -1;
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
