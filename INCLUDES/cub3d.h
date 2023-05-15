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
typedef union u_color			t_color;

// STRUCT ---------------------------------------
struct s_data
{
	int		**map;
	int		color;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_color	floor;
	t_color	ceiling;
};

struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
};

union u_color
{
	unsigned int	color;
	struct s_rgb	rgb;
};

// ENUM -----------------------------------------
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

enum e_cardinal
{
	N,
	S,
	E,
	W
};

// PARSING --------------------------------------
t_exit	parsing(int ac, char **av);

// UTILS ----------------------------------------
char	**split_(char const *s);
int		atoi_(char *s);
int		str_len(char *str);
t_bool	str_end_with(char *s1, char *s2);
char	*get_next_line(int fd);
t_bool	str_n_str(char *s1, char *s2, int n);

#endif
