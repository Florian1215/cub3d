/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:59:55 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/03 15:48:57 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// INCLUDE --------------------------------------
# ifdef __APPLE__
#  include "../mlx/mac/mlx.h"
# endif

# ifdef __linux__
#  include "../mlx/linux/mlx.h"
# endif

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

// DEFINE ---------------------------------------
# define WIN_WIDTH			1080
# define WIN_HEIGHT			720

# define MINIMAP_SIZE		300
# define MINIMAP_OFFSET		20

# define FOV_RANGE			800
# define FOV				90
# define DEFINITION			0.05
# define NUMBER				1

# define MALLOC_ERROR_MSG	"Out of memory"

// TYPEDEF --------------------------------------
typedef struct s_data			t_data;
typedef struct s_list			t_list;
typedef struct s_img			t_img;
typedef struct s_ico			t_ico;
typedef struct s_dco			t_dco;
typedef struct s_collision		t_collision;
typedef struct s_player			t_player;
typedef struct s_map			t_map;
typedef struct s_distances		t_distances;
typedef struct s_straight		t_straight;
typedef enum e_case				t_case;
typedef enum e_file				t_file;
typedef enum e_bool				t_bool;
typedef enum e_exit				t_exit;
typedef enum e_side				t_side;
typedef enum e_keycode			t_keycode;
typedef enum e_cardinal			t_cardinal;
typedef enum e_parsing_state	t_parsing_state;
typedef union u_color			t_color;

// STRUCT ---------------------------------------
struct s_dco
{
	double	x;
	double	y;
};

struct s_ico
{
	int	x;
	int	y;
};

enum e_fd
{
	STDIN,
	STDOUT,
	STDERR,
};

enum e_file
{
	FILE_,
	DIRECTORY,
	NO_FILE,
};

// PARSING --------------------------------------
# ifdef __linux__

enum e_keycode
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 3,
	SCROLL_IN = 4,
	SCROLL_OUT = 5,
	C = 99,
	Q = 113,
	A = 97,
	W = 119,
	S = 115,
	D = 100,
	ESQ = 65307,
	TAB = 65289,
	SPACE = 32,
	PLUS = 65451,
	MINUS = 65453,
	LEFT_KEY = 65361,
	UP_KEY = 65362,
	RIGHT_KEY = 65363,
	DOWN_KEY = 65364,
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

# endif

# ifdef __APPLE__

enum e_keycode
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	SCROLL_IN = 4,
	SCROLL_OUT = 5,
	C = 8,
	Q = 12,
	A = 0,
	W = 13,
	S = 1,
	D = 2,
	ESQ = 53,
	TAB = 48,
	SPACE = 49,
	PLUS = 69,
	MINUS = 78,
	LEFT_KEY = 123,
	UP_KEY = 126,
	RIGHT_KEY = 124,
	DOWN_KEY = 125,
	NUM_0 = 82,
	NUM_1 = 83,
	NUM_2 = 84,
	NUM_3 = 85,
	NUM_4 = 86,
	NUM_5 = 87,
	NUM_6 = 88,
	NUM_7 = 89,
	NUM_8 = 91,
	NUM_9 = 92,
	PAV_0 = 82,
	PAV_1 = 83,
	PAV_2 = 84,
	PAV_3 = 85,
	PAV_4 = 86,
	PAV_5 = 87,
	PAV_6 = 88,
	PAV_7 = 89,
	PAV_8 = 91,
	PAV_9 = 92,
};

# endif

// PARSING --------------------------------------

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

enum e_cardinal
{
	NO_PLAYER = -1,
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FACE_ERROR
};

void		parsing(t_data *data, int ac, char **av);
t_exit		parse_file(t_data *data, char *filename, t_bool is_error_msg);
t_map		*map_new(void);
t_map		*map_last(t_map *m);
void		map_add_back(t_map **start, t_map *new);
t_exit		parse_map(t_map *map);
t_exit		parse_content(t_map *map, char *line);

// MAP ------------------------------------------
enum e_case
{
	INVALID_PLAYER = -2,
	INVALID_CHAR = -1,
	EMPTY_SPACE,
	WALL,
	NOTHING,
	PLAYER,
	VALID
};

struct	s_collision
{
	t_dco	wall;
	double	distance;
	int		side;
};

struct	s_straight
{
	double	a;
	double	b;
};

struct	s_distances
{
	double	*distance;
	int		*face;
	double	*angle;
	int		size;
};

void		map_clear(t_map **map);
void		print_minimap(t_data *data, t_map *map, t_ico offset);
void		draw_square(t_img *img, t_ico co, int size, int color);
void		draw_line(t_data *data, t_dco p1, t_dco p2, int color);
t_collision	draw_fov_line(t_data *data, t_dco p1, t_dco p2, double angle, \
				t_ico offset);
void		draw_rectangle(t_img *img, t_ico co, t_ico size, int color);
void		draw_circle(t_img *img, t_ico co, int radius, int color);
void		draw_round_square(t_img *img, t_ico co, int size, int radius, \
				int color);
void		draw_qcircle(t_img *img, t_ico co, int radius, int q, int color);
int			get_map_coordinates(t_data *data, double co, double move);

// PLAYER ---------------------------------------
void		set_player_position(t_map *map, int k, int i);
void		print_player(t_data *data, t_map *map, t_ico offset);
void		move_player(t_data *data);
void		rotate_player(t_data *data, int keycode);
void		draw_fov(t_data	*data, t_ico offset);

// MATHS ----------------------------------------
double		sqrt_(double num);
double		dpow(double num, int pow);
int			ipow(int num, int pow);
t_bool		is_even(int n);
double		distance_between_points(t_dco p1, t_dco p2);

// RAYCASTING -----------------------------------
void		raycasting(t_data *data);

// MENU -----------------------------------------
void		set_menu(t_data *data);
void		handle_menu(t_data *data);

// UTILS ----------------------------------------
enum e_exit
{
	SUCCESS,
	ERROR,
	ERROR_MALLOC,
};

enum e_bool
{
	FALSE,
	TRUE,
};

char		**split_(char const *s, char sep);
void		free_split(char **split);
void		**free_n_split(void **split, int i);
int			atoi_(char *s);
char		*get_next_line(int fd);
t_exit		error_msg(t_bool print, const char *format, ...);
double		degre_to_radian(double angle);
double		radian_to_degre(double radian);
enum e_file	get_file_type(char *path);
int			get_tab_size(char **tab);

	// STR
char		*str_str(char *s1, char *s2);
int			str_len(char *str);
char		*str_join(char *s1, char *s2);
t_bool		str_end_with(char *s1, char *s2);
char		*str_dup(char *s);

	// LST
struct s_list
{
	char	*line;
	t_list	*next;
};

t_exit		lst_new(t_list **lst, char *line);
int			lst_size(t_list *lst);
int			lst_max_len(t_list *lst);
void		lst_clear(t_list **lst);

	// MLX
enum e_side
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
};

struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
};

union u_color
{
	int				color;
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

void		mlx_pixel_put_img(t_img *img, int x, int y, int color);
void		set_hook(t_data *data);
int			close_mlx_success(t_data *data);
void		close_mlx(t_data *data, t_exit exit_status);

	// init
struct s_map
{
	t_case			**m;
	int				height;
	int				width;
	double			direction;
	t_ico			start_pos;
	t_dco			pos;
	double			hitbox;
	double			hhitbox;
	double			qhitbox;
	double			square_size;
	char			*texture_path[4];
	t_color			color[2];
	t_bool			is_error_msg;
	int				fd;
	t_list			*lst;
	t_parsing_state	state;
	t_ico			offset_map_menu;
	t_ico			start_offset_map;
	t_map			*next;
};

struct s_data
{
	t_bool		is_menu;
	t_bool		is_launch_animation;
	t_bool		is_menu_animation;
	t_map		*map;
	t_bool		key_arrow_press[4];
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_ico		offset_minimap;
	t_distances	distances;
};

void		init_data(t_data *data);
void		render(t_data *data);
int			animation(double a, double b, int i);

#endif
