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

static void	print_background(t_data *data);

void	render(t_data *data)
{
	print_background(data);
	move_player(data);
	raycasting(data);
	print_minimap(data, data->map, (t_ico){MINIMAP_OFFSET, MINIMAP_OFFSET});
	if (!data->is_menu)
		print_fov(data);
	print_player(data, data->map, (t_ico){MINIMAP_OFFSET, MINIMAP_OFFSET});
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}

void	draw_square(t_data *data, t_ico co, double size, int color)
{
	t_ico	i;

	i.x = 0;
	while (i.x < size)
	{
		i.y = 0;
		while (i.y < size)
		{
			mlx_pixel_put_img(&data->img, co.x + i.x, co.y + i.y, color);
			i.y++;
		}
		i.x++;
	}
}

static void	print_background(t_data *data)
{
	const t_color	c[2] = {{0xB6EAFA}, {0x884A39}};
	t_ico			i;

	i.x = 0;
	while (i.x < WIN_WIDTH)
	{
		i.y = 0;
		while (i.y < WIN_HEIGHT)
		{
			mlx_pixel_put_img(&data->img, i.x, i.y, \
				c[i.y > WIN_HEIGHT / 2].color);
			i.y++;
		}
		i.x++;
	}
}

void	draw_line(t_data *data, t_dco p1, t_dco p2, int color)
{
	t_dco	delta;
	float	max;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	max = fmax(fabs(delta.x), fabs(delta.y));
	delta.x /= max;
	delta.y /= max;
	while (((int)(p1.x - p2.x) || (int)(p1.y - p2.y)))
	{
		mlx_pixel_put_img(&data->img, (int)p1.x, (int)p1.y,
			color);
		p1.x += delta.x;
		p1.y += delta.y;
	}
}
