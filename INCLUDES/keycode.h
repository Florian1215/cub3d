/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:58:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/25 17:58:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODE_H
# define KEYCODE_H

enum e_keypress
{
	KP_ERROR = -1,
	KP_UP,
	KP_DOWN,
	KP_LEFT,
	KP_RIGHT,
	KP_I,
	KP_O,
	KP_SHIFT,
};

# ifdef __linux__

enum e_keycode
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 3,
	Q = 113,
	A = 97,
	W = 119,
	S = 115,
	D = 100,
	E = 101,
	SHIFT = 65505,
	ESQ = 65307,
	TAB = 65289,
	LEFT_KEY = 65361,
	RIGHT_KEY = 65363,
	NUM_1 = 49,
	NUM_2 = 50,
	NUM_3 = 51,
	NUM_4 = 52,
	PAV_1 = 65436,
	PAV_2 = 65433,
	PAV_3 = 65435,
	PAV_4 = 65430,
};
# endif

# ifdef __APPLE__

enum e_keycode
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	Q = 12,
	A = 0,
	W = 13,
	S = 1,
	D = 2,
	E = 65505,
	SHIFT = 65505,
	ESQ = 53,
	TAB = 48,
	LEFT_KEY = 123,
	RIGHT_KEY = 124,
	DOWN_KEY = 125,
	NUM_1 = 83,
	NUM_2 = 84,
	NUM_3 = 85,
	NUM_4 = 86,
	PAV_1 = 83,
	PAV_2 = 84,
	PAV_3 = 85,
	PAV_4 = 86,
};
# endif

#endif
