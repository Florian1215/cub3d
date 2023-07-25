/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:58:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/25 17:58:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPROCESSING_H
# define PREPROCESSING_H

// INCLUDE --------------------------------------
# ifdef __APPLE__
#  include "../mlx/mac/mlx.h"
# endif

# ifdef __linux__
#  include "../mlx/linux/mlx.h"
# endif

# include "keycode.h"
# include "typedef.h"
# include "utils.h"

# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>

// DEFINE ---------------------------------------
# define WIN_WIDTH			1080
# define WIN_HEIGHT			720

# define MINIMAP_SIZE		300
# define MINIMAP_OFFSET		20

# define FOV_RANGE			800
# define FOV				90
# define DEFINITION			0.05
# define NUMBER				1
# define FRAME				20
# define PLAYER_ROTATE		1
# define KEYPRESS			6

# define MALLOC_ERROR_MSG	"Out of memory"

#endif
