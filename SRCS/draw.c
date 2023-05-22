/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:26:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/22 13:45:52 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	draw_square(t_data *data, t_co co, double size, t_color color)
{
	int			x;
	int			y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			mlx_pixel_put_img(&data->img, MINIMAP_OFFSET + co.x + x, MINIMAP_OFFSET + co.y + y, color.color);
			y++;
		}
		x++;
	}
}

void	draw_line(t_data *data, t_co p1, t_co p2)
{
	t_co	delta;
	float			max;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	max = fmax(fabs(delta.x), fabs(delta.y));
	delta.x /= max;
	delta.y /= max;
	while (((int)(p1.x - p2.x) || (int)(p1.y - p2.y)))
	{
		mlx_pixel_put_img(&data->img, (int)p1.x, (int)p1.y, \
			0x30888888);
		p1.x += delta.x;
		p1.y += delta.y;
	}
}

// t_collision	draw_fov_line(t_data *data, t_co p1, t_co p2)
// {
// 	t_collision		collision;
// 	t_co			delta;
// 	float			max;

// 	delta.x = p2.x - p1.x;
// 	delta.y = p2.y - p1.y;
// 	max = fmax(fabs(delta.x), fabs(delta.y));
// 	delta.x /= max;
// 	delta.y /= max;
// 	while (((int)(p1.x - p2.x) || (int)(p1.y - p2.y)))
// 	{
// 		if (data->map[(int)((p1.y + MINIMAP_OFFSET) / data->square_size)][(int)((p1.x + MINIMAP_OFFSET) / data->square_size)] != WALL)
// 		{
// 			collision.wall = (t_co){(int)(p1.x / data->square_size), (int)(p1.y / data->square_size)};
// 			collision.distance = distance_between_points(p1, collision.wall);
// 			return (collision);
// 		}
// 		mlx_pixel_put_img(&data->img, (int)p1.x, (int)p1.y, 
// 			0x30888888);
// 		p1.x += delta.x;
// 		p1.y += delta.y;
// 	}
// 	collision.distance = distance_between_points(p1, p2);
// 	return (collision);
// }

static int	compute_coordinates(t_data *data, double co, double move)
{
	return ((int)((co + move + (PLAYER_HITBOX / 2)) / data->square_size));
}

t_collision	draw_fov_line(t_data *data, t_co p1, t_co p2)
{
	t_collision		collision;
	t_co			delta;
	float			max;
	int				x;
	int				y;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	max = fmax(fabs(delta.x), fabs(delta.y));
	delta.x /= max;
	delta.y /= max;
	while (((int)(p1.x - p2.x) || (int)(p1.y - p2.y)))
	{
		x = compute_coordinates(data, p1.x, 0);
		// (void)x;
		(void)y;
		y = compute_coordinates(data, p1.y, 0);
		if (data->map[compute_coordinates(data, p1.y, 0)][x] != WALL)
		{
			collision.wall = (t_co){(int)(p1.x / data->square_size), (int)(p1.y / data->square_size)};
			collision.distance = distance_between_points(p1, collision.wall);
			// return (collision);
		}
		else
			mlx_pixel_put_img(&data->img, (int)p1.x, (int)p1.y, \
			0x30888888);
		p1.x += delta.x;
		p1.y += delta.y;
	}
	collision.distance = distance_between_points(p1, p2);
	return (collision);
}