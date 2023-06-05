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

static t_exit	read_file(t_map *map);
static t_exit	parse_line(t_map *map, char *line);

void	parsing(t_data *data, int ac, char **av)
{
	ac--;
	av++;
	if (!ac)
		open_dir(data, NULL);
	else if (ac == 1)
	{
		if (str_end_with(*av, EXT_MAP))
			parse_file(data, *av, TRUE); // TODO EXIT
		else
			open_dir(data, *av);
	}
	else
		error_msg(TRUE, "./cub3d [directory|*.cub]?");
}

t_exit	parse_file(t_data *data, char *filename, t_bool is_error_msg)
{
	t_map			*map;
	t_exit			exit_status;

	if (!str_end_with(filename, EXT_MAP))
		return (error_msg(is_error_msg, "%s: file does not extension " \
			"match .cub", filename));
	map = map_new();
	if (!map)
		error_msg(is_error_msg, "Out of memory");
	map->is_error_msg = is_error_msg;
	map->fd = open(filename, O_RDONLY);
	if (map->fd == -1)
		return (error_msg(is_error_msg, "%s: %s", filename, strerror(errno)));
	exit_status = read_file(map);
	close(map->fd);
	if (exit_status == SUCCESS && parse_map(map) == SUCCESS)
		return (map_add_back(&data->map, map), SUCCESS);
// TODO	free() m
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
		return (SUCCESS);
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
