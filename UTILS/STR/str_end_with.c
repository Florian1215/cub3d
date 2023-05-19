/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_end_with.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/15 18:23:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/cub3d.h"

t_bool	str_end_with(char *s1, char *s2)
{
	int	i1;
	int	i2;

	if (!*s1 && *s2)
		return (FALSE);
	i1 = str_len_(s1);
	i2 = str_len_(s2);
	while (--i1 > 0 && --i2 > 0)
	{
		if (s1[i1] != s2[i2])
			return (FALSE);
	}
	return (TRUE);
}
