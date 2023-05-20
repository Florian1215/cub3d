/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:59:55 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:40 by fguirama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "../mlx/mlx.h"

//// open, close, read, write, printf, malloc, free, perror, strerror, exit

// DEFINE ---------------------------------------
# define WIN_WIDTH		1080
# define WIN_HEIGHT		720
# define MINIMAP_SIZE	300

# define PLAYER_HITBOX	5

# define ERROR_SEP		": "

// TYPEDEF --------------------------------------
typedef struct s_data			t_data;
typedef struct s_list			t_list;
typedef struct s_img			t_img;
typedef struct s_co				t_co;
typedef enum e_map				t_map;
typedef enum e_bool				t_bool;
typedef enum e_exit				t_exit;
typedef enum e_keycode			t_keycode;
typedef enum e_cardinal			t_cardinal;
typedef enum e_parsing_state	t_parsing_state;
typedef union u_color			t_color;

// STRUCT ---------------------------------------
struct s_co
{
	double	x;
	double	y;
};

struct s_list
{
	char	*line;
	t_list	*next;
};

struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
};

enum e_keycode
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 3,
	SCROLL_IN = 4,
	SCROLL_OUT = 5,
	C = 99,
	D = 100,
	Q = 113,
	ESQ = 65307,
	TAB = 65289,
	SPACE = 32,
	PLUS = 65451,
	MINUS = 65453,
	LEFT = 65361,
	RIGHT = 65363,
	NUM_0 = 48,
	NUM_1 = 49,
	NUM_2 = 50,
	NUM_3 = 51,
	NUM_4 = 52,
	NUM_5 = 53,
	NUM_6 = 54,
	NUM_7 = 55,
	NUM_8 = 56,
	NUM_9 = 57,
	PAV_0 = 65438,
	PAV_1 = 65436,
	PAV_2 = 65433,
	PAV_3 = 65435,
	PAV_4 = 65430,
	PAV_5 = 65437,
	PAV_6 = 65432,
	PAV_7 = 65429,
	PAV_8 = 65431,
	PAV_9 = 65434,
};

union u_color
{
	unsigned int	color;
	struct s_rgb	rgb;
};

struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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

enum e_cardinal
{
	NO_PLAYER = -1,
	NORTH,
	SOUTH,
	WEST,
	EAST
};

enum e_parsing_state
{
	NO,
	SO,
	WE,
	EA,
	FLOOR,
	CEILING,
	MAP_NEWLINE,
	MAP
};

enum e_map
{
	INVALID_CHAR = -1,
	EMPTY_SPACE,
	WALL,
	NOTHING,
	PLAYER
};

struct s_data
{
	t_map		**map;
	int			height;
	int			width;
	double		square_size;
	char		*texture_path[4];
	t_cardinal	player_orientation; // TODO remake position player
	t_co		player_position;
	t_color		floor;
	t_color		ceiling;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
};

// PARSING --------------------------------------
t_exit	parsing(t_data *data, int ac, char **av);
t_exit	parse_map(t_data *data, t_list *lst);
t_exit	parse_content(t_data *data, char *line, t_parsing_state state);
t_exit	check_close_map(t_data *data);

// MAP ------------------------------------------
void	print_minimap(t_data *data);
void	draw_square(t_data *data, t_co co, double size, t_color color);

// PLAYER ---------------------------------------
void	set_player_position(t_data *data, int k, int i);
void	print_player(t_data *data);

// HOOK -----------------------------------------


// UTILS ----------------------------------------
char	**split_(char const *s, char sep);
void	free_split(char **split);
void	**free_n_split(void **split, int i);
int		atoi_(char *s);
char	*get_next_line(int fd);
t_exit	print_error(char *s1, char *s2);

	// STR
t_bool	str_str(char const *s1, char const *s2);
int		str_len_(char *str);
t_bool	str_end_with(char *s1, char *s2);
char	*str_dup(char *s);
void	put_str_fd(char *s, int fd);

	// LST
t_exit	lst_new(t_list **lst, char *line);
int		lst_size(t_list *lst);
void	lst_clear(t_list **lst);

	// MLX
void	mlx_pixel_put_img(t_img *img, int x, int y, int color);
void	set_hook(t_data *data);
int		close_mlx(t_data *data);

	// init
void	init_data(t_data *data);
t_co	init_coordinate(double x, double y);

#endif
