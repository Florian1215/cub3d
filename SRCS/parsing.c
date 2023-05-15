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

static t_exit	parse_file(char *filename);
static void		parse_line(char *line);

t_exit	parsing(int ac, char **av)
{
	if (ac != 1)
		return (ERROR); // TODO Error
	if (!str_end_with(av[0], ".cub"))
		return (ERROR); // TODO Error
	parse_file(av[0]);
	return (SUCCESS);
}

static t_exit	parse_file(char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ERROR); // erno str_error perror
	while (TRUE)
	{
		line = get_next_line(fd);
		parse_line(line);
		if (!line)
			break ;
		free(line);
	}
}

static void	parse_line(char *line)
{
	static char	*identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};


}
