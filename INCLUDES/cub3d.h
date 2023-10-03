/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:59:55 by fguirama          #+#    #+#             */
/*   Updated: 2023/06/03 15:48:57 by mfinette         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "preprocessing.h"

// PARSING --------------------------------------
enum e_parsing_state
{
	PARSING_NO,
	PARSING_SO,
	PARSING_WE,
	PARSING_EA,
	PARSING_DOOR,
	PARSING_FLOOR,
	PARSING_CEILING,
	PARSING_MAP_NEWLINE,
	PARSING_MAP
};

enum e_wall
{
	NO_PLAYER = -1,
	NORTH,
	SOUTH,
	WEST,
	EAST,
	DOOR
};

void		parsing(t_data *data, int ac, char **av);
t_exit		parse_file(t_data *data, char *filename, t_bool is_error_msg);
t_map		*map_new(void);
t_map		*map_last(t_map *m);
void		map_add_back(t_map **start, t_map *new);

// MAP ------------------------------------------
enum e_case
{
	INVALID_PLAYER = -2,
	INVALID_CHAR = -1,
	FLOOR,
	WALL,
	DOOR_OPEN,
	DOOR_CLOSE,
	DOOR_ANIMATION,
	NOTHING,
	PLAYER,
	SPRITE,
	CHECK_FLOOR,
	CHECK_DOOR,
};

enum e_side
{
	VALID_POS = 0,
	TOP_LEFT = 1,
	TOP_RIGHT = 2,
	TOP = 3,
	BOT_LEFT = 4,
	LEFT = 5,
	BOT_RIGHT = 8,
	RIGHT = 10,
	BOT = 12,
};

int			map_size(t_map *m);
void		map_clear(t_map **map, void *mlx_ptr);
t_ico		get_map_ico(t_map *map, t_ico offset);
t_dco		get_map_dco(t_map *map, t_ico offset);
void		draw_minimap(t_data *data, t_map *map, t_ico offset);
t_bool		is_valid_pos(t_map *map, t_dco p1, t_dco p2);

// DRAW -----------------------------------------
struct s_draw
{
	t_img	*img;
	int		color;
	int		radius;
};

double		animation(double a, double b, int i);
void		render(t_data *data);
void		draw_alpha(t_img *img, t_img *alpha, t_ico pos, double ratio);
void		draw_square(t_draw d, t_ico co, int size);
void		draw_round_square(t_draw d, t_ico co, int size);
void		draw_rectangle(t_draw d, t_ico co, t_ico size);
void		draw_round_rectangle(t_draw d, t_ico co, t_ico size);
void		draw_circle(t_draw d, t_ico co);
void		draw_qcircle(t_draw d, t_ico co, int q);
void		draw_line(t_data *data, t_dco p1, t_dco p2, int color);

// PLAYER ---------------------------------------
void		init_player_position(t_map *map, int y, int x);
void		update_direction(t_data *dat);
void		draw_player(t_data *data, t_map *map, t_ico offset);
double		rotate_degre(double a);
t_bool		is_look_down(t_data *data);
t_bool		is_look_up(t_data *data);
t_bool		is_look_left(t_data *data);


// DOOR -----------------------------------------
struct s_door
{
	t_bool	is_scope;
	t_bool	is_opening;
	t_bool	is_animation;
	int		i;
	t_ico	co;
	double	pos;
	int		start;
	int		end;
};

void		stop_door_animation(t_data *data);

// RAYCASTING -----------------------------------
struct s_raycatsing
{
	t_wall	wall;
	double	distance;
	t_dco	pos;
	t_dco	direction;
	t_dco	ray;
	t_dco	co;
	t_ico	co_door;
	t_ico	map_i;
	t_ico	map_step;
	t_dco	step;
	t_dco	line;
	t_bool	is_door;
	t_bool	is_open_door;
	t_bool	is_active;
};

void		raycasting(t_data *data);
void		set_co_ray(t_data *data, t_raycatsing *r);

// MENU -----------------------------------------
enum e_menus
{
	POS_ERROR = -1,
	POS_1,
	POS_2,
	POS_3,
	POS_4,
	FOV_70,
	FOV_90,
	FOV_110,
	LVL_EASY,
	LVL_NORMAL,
	LVL_HARD,
	FOV_TITLE,
	LVL_TITLE,
	FOV_BG,
	LVL_BG,
	LOGO,
};

struct	s_menu
{
	t_ico	pos;
	t_ico	size;
};

struct s_slider
{
	int		i;
	t_bool	animation;
	t_menus	s;
	t_menus	prev;
	double	x;
	double	prev_x;
	t_img	imgs[4];
	t_bool	is_color;
	t_color	colors[3];
	int		c;
	t_color	prev_color;
};

void		render_menu(t_data *data);
void		handle_menu(t_data *data);

// SPRIT ----------------------------------------
struct s_sprite
{
	t_dco		co;
	t_dco		rel_pos;
	int			x;
	t_bool		is_collected;
	t_ico		size;
	t_ico		screen;
	t_ico		texture;
	t_ico		start;
	t_ico		end;
	t_sprite	*next;
};

void		init_sprite(t_map *map, int y, int x);
t_sprite	*sprite_last(t_sprite *m);
void		sprite_clear(t_sprite **sprite, void *mlx_ptr);

// DATA -----------------------------------------
struct s_texture
{
	t_bool	is_texture;
	t_img	img;
	int		color;
	char	*path;
};

struct s_map
{
	t_case			**m;
	int				height;
	int				width;
	t_dco			direction;
	double			degre;
	double			radian;
	t_ico			start_pos;
	t_dco			pos;
	double			hitbox;
	double			hhitbox;
	double			square_size;
	t_texture		t[5];
	t_bool			is_load_texture;
	int				color[2];
	t_bool			is_error_msg;
	int				fd;
	t_list			*lst;
	t_parsing_state	state;
	t_ico			omap_menu;
	t_ico			start_omap;
	t_sprite		*s;
	t_map			*next;
	t_dco			fov;
};

struct s_data
{
	t_dco			fov_value;
	t_slider		fov;
	t_slider		lvl;
	t_menu			menu[BINDS];
	pthread_mutex_t	mutex_i;
	pthread_mutex_t	mutex_render;
	int				i;
	t_menus			hover;
	t_bool			hover_animation;
	t_bool			in_menu;
	t_bool			launch_animation;
	t_slider		slide;
	t_bool			menu_animation;
	t_bool			keypress[KEYPRESS];
	t_bool			mouse_press;
	int				mouse_cursor;
	t_map			*map;
	int				n_map;
	void			*mlx_ptr;
	void			*win_ptr;
	t_dco			fov_line[WIDTH];
	double			sprite_distance[WIDTH];
	t_img			img;
	t_img			logo;
	t_img			sprite_img;
	t_ico			size_slider;
	t_door			door;
	t_ico			txt_pos;
	t_ico			v_pos;
};

void		init_data(t_data *data);
void		set_fov(t_data *data);

#endif
