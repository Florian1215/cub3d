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

void	init_sprites(t_data *data)
{
	data->sprites[0].co = (t_dco){1.5, 1.5};
	data->sprites[1].co = (t_dco){8.5, 1.5};
	data->sprites[2].co = (t_dco){4.5, 6.5};
	data->sprites[3].co = (t_dco){8.5, 6.5};
	data->sprites[4].co = (t_dco){6.5, 3.5};
}

// Fonction pour calculer la norme (longueur) d'un vecteur
double	vector_length(t_dco i)
{
	return (sqrt_(i.x * i.x + i.y * i.y));
}

// Fonction pour calculer le produit scalaire de deux vecteurs
double dot_product(t_dco p1, t_dco p2)
{
	return (p1.x * p2.x + p1.y * p2.y);
}

// Fonction pour vérifier si un sprite est dans le champ de vision du joueur
t_bool	is_sprite_in_fov(t_data *data, t_sprite *sprite, double hfov)
{
	t_dco	to_sprite;

	to_sprite.x = sprite->co.x - data->map->pos.x;
	to_sprite.y = sprite->co.y - data->map->pos.y;

	// Normalisation du vecteur joueur-sprite
	double toSpriteLength = vector_length(to_sprite);
	to_sprite.x /= toSpriteLength;
	to_sprite.y /= toSpriteLength;

	// Calcul de l'angle entre la direction du joueur et le vecteur joueur-sprite
	double angle = acos(dot_product(data->map->direction, to_sprite));

	// Conversion de l'angle en degrés
	angle = radian_to_degre(angle);

	// Vérification si l'angle est dans le champ de vision du joueur
	if (angle > hfov)
		return (FALSE);
	sprite->x = (WIDTH / 2) + angle * (WIDTH / 2) / hfov;
//	printf("Angle %f | x %d\n", angle, sprite->x);
	return (TRUE);
}

void	add_sprites_in_field_of_view(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data->sprites[i].is_in_fov = is_sprite_in_fov(data, \
			data->sprites + i, 90.0 / 2);
		if (data->sprites[i].is_in_fov)
			data->sprites[i].distance = distance_between_points(data->map->pos, \
			data->sprites[i].co);
		i++;
	}
}

void	draw_sprites(t_data *data, t_raycatsing *r)
{
	int	i;

	return ;
	i = 0;
	while (i < 5)
	{
		if (data->sprites[i].is_in_fov && r->line.x == data->sprites[i].x \
				&& data->sprites[i].distance < r->distance)
		{
			draw_rectangle((t_draw){&data->img, 0xFF, 0}, \
				(t_ico){r->line.x, HEIGHT / 2}, (t_ico){1, \
				HEIGHT / data->sprites[i].distance});
		}
		i++;
	}

}

void	draw_sprites_minimap(t_data *data, t_ico offset)
{
	int		i;
	double	d;
	t_ico	co;

	d = (data->map->hhitbox / 1.5);
	i = 0;
	while (i < 5)
	{
		co.x = (int)((data->sprites[i].co.x - (d / 2)) * \
			data->map->square_size + offset.x);
		co.y = (int)((data->sprites[i].co.y - (d / 2)) * \
			data->map->square_size + offset.y);
		draw_circle((t_draw){&data->img, SPRITE_COLOR, \
			(int)(d * data->map->square_size)}, co);
		i++;
	}
}
