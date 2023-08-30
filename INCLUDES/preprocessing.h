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
# define TITLE					"cub3d"
# define EXT					".cub"
# define WIN_WIDTH				1080
# define WIN_HEIGHT				720

# define MINIMAP_SIZE			300
# define MINIMAP_OFFSET			20

# define FOV_RANGE				800
# define DEFINITION				0.05
# define NUMBER					1
# define FRAME					20
# define PLAYER_ROTATE			1
# define KEYPRESS				6
# define BINDS					15
# define MENU_PADX				6
# define MENU_RADIUS			12
# define PADX_LVL				19
# define PADY_LVL				184

// ERROR ----------------------------------------
# define ERR_MALLOC				"Out of memory"
# define ERR_OPEN_DIR			"cannot open directory '%s': %s"
# define ERR_NB_ARGS			"Wrong number of arguments"
# define ERR_VALID_MAP			"no valid minimap in '%s' directory"
# define ERR_VALID_ARG_MAP		"None of the maps passed as arguments are valid"
# define ERR_EXT				"Map: %s: file does not match extension %s"
# define ERR_OPEN_MAP			"Map: %s: %s"
# define ERR_TO_MANY_PLAYER		"Map: Too many players"
# define ERR_NO_PLAYER			"Map: No player on the map"
# define ERR_MAP_ID				"Map: not valid identifier find '%s'"
# define ERR_MAP_MISS_INFO		"Map: Miss information"
# define ERR_MAP_NO_CLOSE		"Map: Not close map"
# define ERR_MAP_INVALID_CHAR	"Invalid char '%c'"

// PATH -----------------------------------------
# define PATH_MAP_DIR			"./MAPS"
# define PATH_LOGO				"./ASSET/logo.xpm"
# define PATH_70				"./ASSET/70.xpm"
# define PATH_90				"./ASSET/90.xpm"
# define PATH_110				"./ASSET/110.xpm"
# define PATH_FOV				"./ASSET/FOV.xpm"
# define PATH_EASY				"./ASSET/easy.xpm"
# define PATH_NORMAL			"./ASSET/normal.xpm"
# define PATH_HARD				"./ASSET/hard.xpm"
# define PATH_LVL				"./ASSET/LEVEL.xpm"

// COLOR ----------------------------------------
# define BG_MENU				0x7EAA92
# define BG_ITEM_MENU			0xC8E4B2
# define BG_ITEM_MENU_HOVER		0xFFF2CC
# define WALL_COLOR				0xFF0060
# define FLOOR_COLOR			0xFFE79B
# define DOOR_OPEN_COLOR		0xB9B4C7
# define DOOR_CLOSE_COLOR		0x5C5470
# define PLAYER_COLOR			0x4C4C6D
# define FOV_COLOR				0x5C8984

# define EASY_COLOR				0xFAE392
# define NORMAL_COLOR			0xF0B86E
# define HARD_COLOR				0xE48586

// MATHS ----------------------------------------
# define PI						3.1415926
# define PI2					(PI / 2)
# define PI3					(3 * M_PI / 2)

#endif
