/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:32:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/19 19:32:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

static void	put_cub3d(void);

t_exit	print_error(char *s1, char *s2)
{
	put_cub3d();
	put_str_fd(s1, STDERR_FILENO);
	if (s2)
	{
		put_str_fd(ERROR_SEP, STDERR_FILENO);
		put_str_fd(s2, STDERR_FILENO);
	}
	put_str_fd("\033[0m\n", STDERR_FILENO);
	return (ERROR);
}

static void	put_cub3d(void)
{
	put_str_fd("\033[91m", STDERR_FILENO);
	put_str_fd("cub3d", STDERR_FILENO);
	put_str_fd(ERROR_SEP, STDERR_FILENO);
	put_str_fd("\033[90m", STDERR_FILENO);
}
