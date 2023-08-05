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
};

# ifdef __linux__

enum e_keycode
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 3,
	SCROLL_IN = 4,
	SCROLL_OUT = 5,
	COMMA = 44,
	DOT = 46,
	C = 99,
	Q = 113,
	A = 97,
	W = 119,
	S = 115,
	D = 100,
	I = 105,
	O = 111,
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
	O = 31,
	I = 34,
	COMMA = 43,
	DOT = 47,
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

#endif
