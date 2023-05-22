/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pow.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:15:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/22 19:15:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/cub3d.h"

double	pow_(double num, int pow)
{
	double	res;

	res = 1;
	while (pow > 0)
	{
		res *= num;
		pow--;
	}
	return (res);
}
