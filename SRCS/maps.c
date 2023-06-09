/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 22:07:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/05 22:07:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

void	change_map(t_data *data)
{
	t_map	*tmp;

	if (!data->map->next)
		return ;
	tmp = data->map;
	data->map = data->map->next;
	tmp->next = NULL;
	map_last(data->map)->next = tmp;
}

void	change_n_map(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		change_map(data);
		i++;
	}
}
