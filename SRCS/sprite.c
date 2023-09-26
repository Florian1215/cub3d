/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:10:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/09/26 19:10:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprites(t_data *data)
{
	data->sprites[0].co = (t_dco){1.5, 1.5};
	data->sprites[1].co = (t_dco){8.5, 1.5};
	data->sprites[2].co = (t_dco){4.5, 7.5};
	data->sprites[3].co = (t_dco){8.5, 7.5};
	data->sprites[4].co = (t_dco){6.5, 3.5};
}
