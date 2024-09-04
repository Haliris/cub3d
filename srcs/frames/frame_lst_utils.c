/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:39:29 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/04 09:58:46 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"

t_frame	*lst_new(void)
{
	t_frame	*lst;

	lst = (t_frame *)malloc(sizeof(t_frame));
	if (!lst)
		return (NULL);
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

void	lst_add_back(t_frame **lst, t_frame *new_node)
{
	t_frame	*tmp;

	if (!new_node)
		return ;
	if (!(*lst))
	{
		*lst = new_node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	new_node->prev = tmp;
	tmp->next = new_node;
}

void	lst_clear(t_frame **lst, void (*del)(void *))
{
	t_frame	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		del(tmp);
	}
}

t_frame	*lst_last(t_frame *lst)
{
	t_frame	*tmp;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	lst_size(t_frame *lst)
{
	int		i;
	t_frame	*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
