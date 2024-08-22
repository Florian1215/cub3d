/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:56:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/09/10 18:56:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	is_look_up(t_data *data)
{
	return ((DWN < data->map->degre && data->map->degre < DNE));
}

t_bool	is_look_down(t_data *data)
{
	return (DES < data->map->degre && data->map->degre < DSW);
}

t_bool	is_look_left(t_data *data)
{
	return ((DSW < data->map->degre && data->map->degre < DWN));
}
