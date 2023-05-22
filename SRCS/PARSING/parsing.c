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

static t_exit	parse_file(t_data *data, char *filename);
static t_exit	parse_line(t_data *data, char *line, t_list **lst, \
					t_parsing_state *state);

t_exit	parsing(t_data *data, int ac, char **av)
{
	av++;
	ac--;
	if (ac != 1)
		return (ERROR);
	if (!str_end_with(av[0], ".cub"))
		return (ERROR);
	return (parse_file(data, av[0]));
}

static t_exit	parse_file(t_data *data, char *filename)
{
	int				fd;
	char			*line;
	t_list			*lst;
	t_parsing_state	state;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ERROR); // TODO erno str_error perror
	lst = NULL;
	state = NO;
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_line(data, line, &lst, &state) >= ERROR)
			return (lst_clear(&lst), ERROR);
	}
	close(fd);
	if (state == MAP && parse_map(data, lst) == SUCCESS)
		return (SUCCESS);
	return (ERROR);
}

static t_exit	parse_line(t_data *data, char *line, t_list **lst, \
					t_parsing_state *state)
{
	t_exit	exit_status;

	if (*state != MAP && !*line)
		return (SUCCESS);
	if (*state == MAP_NEWLINE)
		++*state;
	if (*state == MAP)
		exit_status = lst_new(lst, line);
	else
	{
		exit_status = parse_content(data, line, *state);
		free(line);
		++*state;
	}
	return (exit_status);
}
