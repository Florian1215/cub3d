/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:04:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/17 16:04:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*str_str(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	if (!s2[i])
		return (s1);
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j] && s1[i + j])
			j++;
		if (!s2[j])
			return (s1 + i + j);
		i++;
	}
	return (NULL);
}
