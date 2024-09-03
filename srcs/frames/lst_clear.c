/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:09:48 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/03 16:37:58 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame.h"

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

/* Note
 * 1. if *lst (or bgn_lst) is NULL, do nothing (already cleared)
 * 2. if function "del" is NULL, it will crash at lstdelone
 */
/*
#include <stdio.h>
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);

void	del_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*begin_list;
	int	a = 3;
	int	b = 4;
	int	i = 0;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*o_next;
	int	*o_data;

	begin_list = ft_lstnew(ft_lstnew(&a));
	tmp = begin_list;
	while (i < 10)
	{
		ft_lstadd_back(&begin_list, ft_lstnew(ft_lstnew(&b)));
		i++;
	}
	printf("content		|current add	|next add\n");
	while (tmp)
	{
		printf("%p 	|%p	|%p\n", ((*tmp).content), tmp, (*tmp).next);
		tmp = (*tmp).next;
	}
	// save original record
	o_next = begin_list->next;
	o_data = begin_list->content;
	// clear the list
	tmp2 = begin_list;
	ft_lstclear(&begin_list, &del_content);
	printf("  ==> after free <==\n");
	printf("bgn_lst	%p,	%p\n", begin_list, &begin_list);
	printf("tmp2	%p,	%p\n", tmp2, &tmp2);
	printf(" ======================= \n");
	printf("data before: %p; after: %p\n", o_data, tmp2->content);
	if (tmp2->content != o_data)
		printf("==> list data no longer exists!\n");
	printf("next before: %p; after: %p\n", o_next, tmp2->next);
	if (tmp2->next != o_next)
		printf("==> list link no longer exists!\n");
	return (0);
}
// The 4 errors are due to tmp2->content and tmp2-> after free
*/
