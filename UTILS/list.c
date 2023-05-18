/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:04:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/05/18 16:04:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/cub3d.h"

static t_list	*lst_last(t_list *lst);

t_exit	lst_new(t_list **lst, char *line)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (free(line), ERROR);
	new->line = line;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
		lst_last(*lst)->next = new;
	return (SUCCESS);
}

static t_list	*lst_last(t_list *lst)
{
	if (!lst || !lst->next)
		return (lst);
	return (lst_last(lst->next));
}

int	lst_size(t_list *lst)
{
	if (!lst)
		return (0);
	return (1 + lst_size(lst->next));
}

void	lst_clear(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
}
