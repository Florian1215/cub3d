/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:32:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/19 19:32:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_cub3d(void);
static void	str_format(char c, va_list	args);
static void	put_char(int c);
static void	put_str(char *s);

t_exit	error_msg(t_bool print, const char *format, ...)
{
	va_list	args;
	int		i;

	if (!print)
		return (ERROR);
	put_cub3d();
	va_start(args, format);
	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			if (!format[++i])
				break ;
			str_format(format[i], args);
		}
		else
			put_char(format[i]);
	}
	va_end(args);
	put_str("\033[0m\n");
	return (ERROR);
}

static void	put_cub3d(void)
{
	put_str("\033[91m");
	put_str("cub3d: ");
	put_str("\033[90m");
	put_str("Error: ");
}

static void	str_format(char c, va_list	args)
{
	if (c == 's')
		return (put_str(va_arg(args, char *)));
	if (c == 'c')
		return (put_char(va_arg(args, int)));
	put_char(c);
}

static void	put_char(int c)
{
	int	res;

	res = write(STDERR_FILENO, &c, 1);
	(void)res;
}

static void	put_str(char *s)
{
	int	res;

	if (s == NULL)
		s = "(null)";
	res = write(STDERR_FILENO, s, str_len(s));
	(void)res;
}
