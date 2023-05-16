/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_n_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:13:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/16 14:13:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

t_bool	str_n_str(char *s1, char *s2, int n)
{
	int	i;
	int	j;

	i = 0;
	if (!*s2)
		return (TRUE);
	while (s1[i] && i < n)
	{
		j = 0;
		while (s1[i + j] == s2[j] && s1[i + j] && i + j < n)
			j++;
		if (!s2[j])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

