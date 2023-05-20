/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/18 19:23:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/cub3d.h"

int			key_event(int k, t_data *data);
int			key_event_press(int k, t_data *data);
int			key_event_release(int k, t_data *data);
int			mouse_event_press(int button, int x, int y, t_data *data);
int			mouse_event_release(int button, int x, int y, t_data *data);
int			mouse_event_motion(int button, int x, int y, t_data *data);
static int	hook_loop(t_data *data);

void	set_hook(t_data *data)
{
	mlx_key_hook(data->win_ptr, key_event, data);
	mlx_hook(data->win_ptr, 2, (1L << 0), key_event_press, data);
	mlx_hook(data->win_ptr, 3, (1L << 1), key_event_release, data);
	mlx_hook(data->win_ptr, 4, (1L << 2), mouse_event_press, data);
	mlx_hook(data->win_ptr, 5, (1L << 3), mouse_event_release, data);
	mlx_hook(data->win_ptr, 6, (1L << 13), mouse_event_motion, data);
	mlx_hook(data->win_ptr, 17, 0, close_mlx, data);
	mlx_loop_hook(data->mlx_ptr, hook_loop, data);
}

static int	hook_loop(t_data *data)
{
	move_player(data);
	return (SUCCESS);
}
