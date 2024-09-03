/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:53:24 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/03 17:27:23 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"

t_frame	*lst_last(t_frame *lst)
{
	t_frame	*tmp;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/* Note
 * 1. if lst is NULL, it will return NULL
 */
/*
#include <stdio.h>
void    ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);

int	main(void)
{
	t_list	*lst;
	t_list	*last;
	int	a = 3;
	int	b = 4;
	int	i = 0;
	t_list	*tmp;

	lst = ft_lstnew(&a);
	while (i < 10)
	{
		ft_lstadd_front(&lst, ft_lstnew(&b));
		i++;
	}
	last = ft_lstlast(lst);
	printf("value of last list is: %d\n", *(int *)(*last).content);
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	return (0);
}*/
