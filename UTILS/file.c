/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:33:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/09 15:33:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

t_file	get_file_type(char *path)
{
	struct stat	s;

	if (stat(path, &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
			return (DIRECTORY);
		else if (s.st_mode & S_IFREG)
			return (FILE_);
	}
	return (NO_FILE);
}
