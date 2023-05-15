/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:36:21 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/09 17:36:21 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// INCLUDE --------------------------------------
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

//// open, close, read, write, printf, malloc, free, perror, strerror, exit

// TYPEDEF --------------------------------------
typedef struct s_data			t_data;
typedef enum e_bool				t_bool;
typedef enum e_exit				t_exit;

// STRUCT ---------------------------------------
struct s_data
{
	int	**map;
	int	color;
};

enum e_bool
{
	FALSE,
	TRUE,
};

enum e_exit
{
	SUCCESS,
	ERROR,
	ERROR_MALLOC,
};

// PARSING --------------------------------------
t_exit	parsing(int ac, char **av);

// UTILS ----------------------------------------
char	**split_(char const *s);
int		atoi_(char *s);

#endif
