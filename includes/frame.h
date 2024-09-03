/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:48:25 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/03 16:52:15 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAME_H
# define FRAME_H

# include <stdlib.h>

typedef struct s_frame
{
	void			*img;
	char			*addr;
	int				frm_h;
	int				frm_w;
	int				bpp;
	int				ll;
	int				endian;
	struct s_frame	*next;
	struct s_frame	*prev;
}	t_frame;

void	lst_add_back(t_frame **lst, t_frame *new_node);
void	lst_clear(t_frame **lst, void (*del)(void *));
t_frame	*lst_last(t_frame *lst);
int		lst_size(t_frame *lst);
t_frame	*lst_new(void);

#endif