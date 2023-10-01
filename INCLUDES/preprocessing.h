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
# include <pthread.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>

// DEFINE ---------------------------------------
# define TITLE					"cub3d"
# define EXT					".cub"
# define WIDTH					2400
# define HEIGHT					1440
# define HHEIGHT				720

# define MINIMAP_SIZE			600
# define MINIMAP_OFFSET			40

# define DEAST					0
# define DES					45
# define DSOUTH					90
# define DSW					135
# define DWEST					180
# define DWN					225
# define DNORTH					270
# define DNE					315

# define FPS					25
# define MAX_THREAD				8
# define ROTATE_SPEED			2.5
# define MOVE_SPEED				0.1
# define KEYPRESS				7
# define BINDS					15
# define PADX_MENU				12
# define PADY_FOV				20
# define MENU_RADIUS			24
# define PADY_LVL				340
# define WIDTH_EDIT				230
# define HEIGHT_EDIT			120
# define RLOGO					0.2
# define RSLIDER				0.06
# define RTITLE					0.15
# define SIZE_V					5

# define MSG_OPEN_DOOR			"press 'E' to close the door"
# define MSG_CLOSE_DOOR			"press 'E' to open the door"

// ERROR ----------------------------------------
# define ERR_MALLOC				"Out of memory"
# define ERR_OPEN_DIR			"cannot open directory '%s': %s"
# define ERR_NB_ARGS			"Wrong number of arguments"
# define ERR_VALID_MAP			"no valid maps in '%s' directory"
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
# define PATH_COINS				"./ASSET/coins.xpm"

// COLOR ----------------------------------------
# define WHITE					0xFFFFFF
# define BG_MENU				0x7EAA92
# define BG_ITEM_MENU			0xC8E4B2
# define BG_ITEM_MENU_HOVER		0xFFF2CC
# define WALL_COLOR				0xFF0060
# define FLOOR_COLOR			0xFFE79B
# define DOOR_CLOSE_COLOR		0x5C5470
# define PLAYER_COLOR			0x4C4C6D
# define FOV_COLOR				0x5C8984
# define SPRITE_COLOR			0x8DDFCB

# define EASY_COLOR				0xFAE392
# define NORMAL_COLOR			0xF0B86E
# define HARD_COLOR				0xE48586

# define NORTH_COLOR			0xD0BFFF
# define SOUTH_COLOR			NORMAL_COLOR
# define WEST_COLOR				HARD_COLOR
# define EAST_COLOR				0xA8DF8E

// MATHS ----------------------------------------
# define PI						3.141592
# define PI2					1.570796

#endif
