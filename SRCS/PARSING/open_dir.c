/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:23:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/05 15:23:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/cub3d.h"

void	open_dir(t_data *data, char *directory)
{
	const char		*default_directory = "./MAPS/";
	DIR				*dir_open;
	struct dirent	*dir_read;

	if (!directory)
		directory = (char *)default_directory;
	dir_open = opendir(directory);
	if (!dir_open)
		error_msg(TRUE, "cannot open directory '%s': %s", \
			directory, strerror(errno));
	while (TRUE)
	{
		dir_read = readdir(dir_open);
		if (!dir_read)
			break ;
		parse_file(data, str_join(directory, dir_read->d_name), FALSE);
	}
	closedir(dir_open);
	if (!data->map)
		error_msg(TRUE, "no valid map in '%s' directory", directory);
}
