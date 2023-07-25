/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:03:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/25 18:03:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

// TYPEDEF --------------------------------------
typedef struct s_data			t_data;
typedef struct s_list			t_list;
typedef struct s_img			t_img;
typedef struct s_ico			t_ico;
typedef struct s_dco			t_dco;
typedef struct s_collision		t_collision;
typedef struct s_map			t_map;
typedef struct s_distances		t_distances;
typedef enum e_case				t_case;
typedef enum e_file				t_file;
typedef enum e_bool				t_bool;
typedef enum e_exit				t_exit;
typedef enum e_keypress			t_keypress;
typedef enum e_parsing_state	t_parsing_state;
typedef union u_color			t_color;
typedef unsigned long long int	t_time;

#endif