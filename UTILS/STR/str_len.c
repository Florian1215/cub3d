/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:13:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/15 18:13:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	str_len_(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}
