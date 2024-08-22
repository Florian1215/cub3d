/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:47:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/15 11:47:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_word(char const *s, char sep);
static int	word_len(char const *s, char sep);
static char	*word_cpy(const char *src, int n);

char	**split_(char const *s, char sep)
{
	char	**split;
	int		n_word;
	int		i;
	int		n;

	n_word = count_word(s, sep);
	split = malloc((n_word + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = -1;
	while (++i < n_word)
	{
		while (*s && *s == sep)
			s++;
		n = word_len(s, sep);
		split[i] = word_cpy(s, n);
		if (!split[i])
			return ((char **)free_n_split((void **)split, i - 1));
		s += n;
	}
	return (split[n_word] = NULL, split);
}

static int	count_word(char const *s, char sep)
{
	int	i;
	int	ct;

	ct = 0;
	while (*s)
	{
		while (*s && *s == sep)
			s++;
		i = word_len(s, sep);
		s += i;
		if (i)
			ct++;
	}
	return (ct);
}

static int	word_len(char const *s, char sep)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != sep)
		len++;
	return (len);
}

static char	*word_cpy(const char *src, int n)
{
	char	*dest;

	dest = malloc((n + 1) * sizeof(char));
	if (!dest)
		return (0);
	dest[n] = '\0';
	while (n--)
		dest[n] = src[n];
	return (dest);
}

void	**free_n_split(void **split, int i)
{
	while (split && i >= 0)
		free(split[i--]);
	free(split);
	return (NULL);
}
