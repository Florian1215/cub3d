/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:06:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/17 16:06:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/cub3d.h"

static t_exit	init_map(t_data *data, t_list *lst);
static int		get_width(t_list *lst);
static t_exit	parse_line_map(t_data *data, char *line);
static t_map	get_char(t_data *data, char c);
int				get_square_size(t_data *data);

t_exit	parse_map(t_data *data, t_list *lst)
{
	t_list	*tmp;

	if (init_map(data, lst))
		return (ERROR_MALLOC);
	tmp = lst;
	while (tmp)
	{
		if (parse_line_map(data, tmp->line) == ERROR)
			return (lst_clear(&lst), ERROR);
		tmp = tmp->next;
	}
	lst_clear(&lst);
	if (data->player_direction == NO_PLAYER || check_close_map(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static t_exit	init_map(t_data *data, t_list *lst)
{
	int	k;

	data->height = lst_size(lst);
	data->map = malloc(sizeof(t_map *) * data->height);
	if (!data->map)
		return (ERROR_MALLOC);
	data->width = get_width(lst);
	k = 0;
	data->square_size = get_square_size(data);
	while (k < data->height)
	{
		data->map[k] = malloc(sizeof(t_map) * data->width);
		if (!data->map[k])
			return (free_n_split((void **)data->map, k - 1), ERROR_MALLOC);
		k++;
	}
	return (SUCCESS);
}

static int	get_width(t_list *lst)
{
	int	max;
	int	len;

	max = -1;
	while (lst)
	{
		len = str_len_(lst->line);
		if (len > max)
			max = len;
		lst = lst->next;
	}
	return (max);
}

static t_exit	parse_line_map(t_data *data, char *line)
{
	static int	k = 0;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < data->width)
	{
		if (line[j])
		{
			data->map[k][i] = get_char(data, line[j]);
			if (data->map[k][i] == INVALID_CHAR)
				return (ERROR);
			if (data->map[k][i] == PLAYER)
				set_player_position(data, k, i);
			j++;
		}
		else
			data->map[k][i] = NOTHING;
		i++;
	}
	k++;
	return (SUCCESS);
}

static t_map	get_char(t_data *data, char c)
{
	if (c == '0')
		return (EMPTY_SPACE);
	else if (c == '1')
		return (WALL);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (c == 'E')
			data->player_direction = 0;
		else if (c == 'N')
			data->player_direction = 90;
		else if (c == 'W')
			data->player_direction = 180;
		else
			data->player_direction = 270;
		return (PLAYER);
	}
	else if (c == ' ')
		return (NOTHING);
	else
		return (INVALID_CHAR);
}
