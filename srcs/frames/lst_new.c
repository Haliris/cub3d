/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:28:30 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/03 16:17:52 by tsuchen          ###   ########.fr       */
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
/*
#include <stdio.h>
int	main(void)
{
	int	a = 7;
	t_list	*lst;

	lst = ft_lstnew(&a);
	printf("val_lst: %d, add_lst: %p\n", *((int *)(lst->content)), lst->content);
	printf("val_a  : %d, add_a  : %p\n", a, &a);
	printf("add of nex in lst: %p\n", lst->next);
	free(lst);
	return (0);
}*/
