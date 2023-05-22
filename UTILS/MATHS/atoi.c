/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:45:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/15 11:45:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

static t_bool	is_digit(int c);

int	atoi_(char *s)
{
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	if (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -sign;
	while (is_digit(*s))
		res = res * 10 + *s++ - '0';
	return (res * sign);
}

static t_bool	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}
