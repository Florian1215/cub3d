/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:58:43 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/29 23:58:43 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	animation(double a, double b, int i)
{
	const double	values[29] = {0.4, 1.7, 4.6, 9.8, 19, \
	32, 44.7, 54.7, 62.4, 68.6, 73.6, 77.7, 81.2, \
	84.2, 86.8, 89, 90.9, 92.5, 93.9, 95.2, 96.2, \
	97.1, 97.8, 98.5, 99, 99.4, 99.6, 99.8, 99.9};

	if (a > b)
		return (a - (values[i] * (a - b) / 100));
	else if (a < b)
		return ((values[i] * (b - a) / 100) + a);
	return (a);
}

void	slide_animation(t_data *data)
{
	static int	i = 0;
	double		*value;

	if (i == 29)
	{
		i = 0;
		data->slide.animation = FALSE;
		return ;
	}
	data->slide.x = animation(100, 0, i) / 100 * WIDTH;
	if (is_look_up(data) || is_look_down(data))
		value = &data->map->pos.x;
	else
		value = &data->map->pos.y;
	if (is_look_up(data) || is_look_left(data))
		*value = animation((int)*value, ceil(*value) - data->map->hhitbox, i);
	else
		*value = animation(ceil(*value), (int)*value + data->map->hhitbox, i);
	i++;
}
