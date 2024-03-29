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

#include "cub3d.h"

static void	read_dir(t_data *data, DIR *dir_open, char *directory);

t_exit	open_dir(t_data *data, char *directory, t_bool is_print)
{
	const char		*default_directory = PATH_MAP_DIR;
	DIR				*dir_open;

	if (!directory)
		directory = (char *)default_directory;
	dir_open = opendir(directory);
	if (!dir_open)
		return (error_msg(is_print, ERR_OPEN_DIR, directory, strerror(errno)));
	read_dir(data, dir_open, directory);
	closedir(dir_open);
	if (!data->map)
		return (error_msg(is_print, ERR_VALID_MAP, directory));
	return (SUCCESS);
}

static void	read_dir(t_data *data, DIR *dir_open, char *directory)
{
	struct dirent	*dir_read;
	char			*abs_path;
	t_file			type_file;

	while (TRUE)
	{
		dir_read = readdir(dir_open);
		if (!dir_read)
			break ;
		if (*dir_read->d_name == '.')
			continue ;
		abs_path = str_join(directory, dir_read->d_name);
		if (!abs_path)
			break ;
		type_file = get_file_type(abs_path);
		if (type_file == FILE_)
			parse_file(data, abs_path, FALSE);
		else if (type_file == DIRECTORY)
			open_dir(data, abs_path, FALSE);
		free(abs_path);
	}
}
