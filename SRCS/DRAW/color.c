/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:26:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/08/14 17:26:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_gradient(t_color c1, t_color c2, int i)
{
	t_color	res;

	res.rgb.r = animation(c1.rgb.r, c2.rgb.r, i);
	res.rgb.g = animation(c1.rgb.g, c2.rgb.g, i);
	res.rgb.b = animation(c1.rgb.b, c2.rgb.b, i);
	return (res.color);
}
