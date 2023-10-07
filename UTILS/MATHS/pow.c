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

#include "cub3d.h"

double	dpow(double num, int pow)
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

int	ipow(int num, int pow)
{
	int	res;

	res = 1;
	while (pow > 0)
	{
		res *= num;
		pow--;
	}
	return (res);
}
