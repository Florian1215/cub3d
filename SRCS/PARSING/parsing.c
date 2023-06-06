/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:44:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/15 11:44:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

t_exit			open_dir(t_data *data, char *directory);
static t_exit	read_file(t_map *map);
static t_exit	parse_line(t_map *map, char *line);

void	parsing(t_data *data, int ac, char **av)
{
	t_exit	exit_status;

	ac--;
	av++;
	if (!ac)
		exit_status = open_dir(data, NULL);
	else if (ac == 1)
	{
		if (str_end_with(*av, EXT_MAP))
		{
			data->is_menu = FALSE;
			exit_status = parse_file(data, *av, TRUE);
		}
		else
			exit_status = open_dir(data, *av);
	}
	else
		error_msg(TRUE, "./cub3d [directory|*.cub]?");
	if (exit_status == ERROR)
		close_mlx(data, ERROR);
}

t_exit	parse_file(t_data *data, char *filename, t_bool is_error_msg)
{
	t_map			*map;
	t_exit			exit_status;

	if (!str_end_with(filename, EXT_MAP))
		return (error_msg(is_error_msg, "Map: %s: file does not match " \
			"extension .cub", filename));
	map = map_new();
	if (!map)
		return (error_msg(is_error_msg, MALLOC_ERROR_MSG));
	map->is_error_msg = is_error_msg;
	map->fd = open(filename, O_RDONLY);
	if (map->fd == -1)
		return (error_msg(is_error_msg, "Map: %s: %s", \
			filename, strerror(errno)));
	exit_status = read_file(map);
	close(map->fd);
	if (exit_status == SUCCESS && parse_map(map) == SUCCESS)
		return (map_add_back(&data->map, map), SUCCESS);
	map_clear(&map);
	return (ERROR);
}

static t_exit	read_file(t_map *map)
{
	char			*line;

	while (TRUE)
	{
		line = get_next_line(map->fd);
		if (!line)
			break ;
		if (parse_line(map, line) >= ERROR)
			return (lst_clear(&map->lst), ERROR);
	}
	if (map->state == MAP)
		return (SUCCESS);
	return (error_msg(map->is_error_msg, "Map: Miss information"));
}

static t_exit	parse_line(t_map *map, char *line)
{
	t_exit	exit_status;

	if (map->state != MAP && !*line)
		return (free(line), SUCCESS);
	if (map->state == MAP_NEWLINE)
		++map->state;
	if (map->state == MAP)
		exit_status = lst_new(&map->lst, line);
	else
	{
		exit_status = parse_content(map, line);
		free(line);
		++map->state;
	}
	return (exit_status);
}
