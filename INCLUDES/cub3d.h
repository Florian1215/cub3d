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

# include "preprocessing.h"

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

struct	s_distances
{
	double	*distance;
	int		*face;
	double	*angle;
	int		size;
};

void		map_clear(t_map **map);
int			get_map_coordinates(t_data *data, double co, double move);
void		print_minimap(t_data *data, t_map *map, t_ico offset);

// DRAW -----------------------------------------
int			animation(double a, double b, int i);
void		render(t_data *data);
void		draw_square(t_img *img, t_ico co, int size, int color);
void		draw_line(t_data *data, t_dco p1, t_dco p2, int color);
t_collision	draw_fov_line(t_data *data, t_dco p1, t_dco p2, double angle, \
				t_ico offset);
void		draw_rectangle(t_img *img, t_ico co, t_ico size, int color);
void		draw_circle(t_img *img, t_ico co, int radius, int color);
void		draw_round_square(t_img *img, t_ico co, int size, int radius, \
				int color);
void		draw_qcircle(t_img *img, t_ico co, int radius, int q, int color);
void		draw_fov(t_data	*data, t_ico offset);

// PLAYER ---------------------------------------
void		set_player_position(t_map *map, int k, int i);
void		update_direction(t_map *map);
void		print_player(t_data *data, t_map *map, t_ico offset);

// MATHS ----------------------------------------
double		sqrt_(double num);
double		dpow(double num, int pow);
int			ipow(int num, int pow);
t_bool		is_even(int n);
double		distance_between_points(t_dco p1, t_dco p2);
t_dco		dco_add(t_dco co1, t_dco co2);
t_dco		dco_mul(t_dco c, double f);
t_time		get_timestamp(void);
void		sleep_until(t_time until);

// RAYCASTING -----------------------------------
void		raycasting(t_data *data);

// MENU -----------------------------------------
void		set_menu(t_data *data);
void		handle_menu(t_data *data);

// DATA -----------------------------------------
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
	double			qhitbox;
	double			square_size;
	double			move_speed;
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
	t_bool		key_arrow_press[KEYPRESS];
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_ico		offset_minimap;
	t_distances	distances;
	t_time		start_animation;
};

void		init_data(t_data *data);

#endif
