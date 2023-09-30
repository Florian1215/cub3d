/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:07:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/25 18:07:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "typedef.h"

// UTILS ---------------------------------------
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

enum e_file
{
	FILE_,
	DIRECTORY,
	NO_FILE,
};

// ARRAY ----------------------------------------
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

// STR ------------------------------------------
char		*str_str(char *s1, char *s2);
int			str_len(char *str);
char		*str_join(char *s1, char *s2);
t_bool		str_end_with(char *s1, char *s2);
char		*str_dup(char *s);

// LST ------------------------------------------
struct s_list
{
	char	*line;
	t_list	*next;
};

t_exit		lst_new(t_list **lst, char *line);
int			lst_size(t_list *lst);
int			lst_max_len(t_list *lst);
void		lst_clear(t_list **lst);

// MLX ------------------------------------------
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

struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		bit_ratio;
	int		line_length;
	int		endian;
	int		width;
	int		height;
};

void		mlx_pixel_put_img(t_img *img, int x, int y, int color);
void		set_hook(t_data *data);
int			close_mlx(t_data *data);
void		init_img(t_img *img, char *path, void *mlx_ptr);
void		dup_img(t_img *img1, t_img *img2);
void		sleep_until(t_time until);
t_time		get_timestamp(void);

#endif
