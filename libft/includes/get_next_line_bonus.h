/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:11:27 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/16 18:20:02 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <unistd.h>
# include "libft.h"
# include <stdlib.h>

char	*get_next_line(int fd);
char	*fetch_line(char *line_stash, int fd, int *status);
char	*trim_buff(char *read_buff);
void	get_stash(char *stash, char *line);
char	*ft_str_rejoin(char *stash, char *append);
int		find_eol(char *str);
void	copy_and_cat(char *out, char *cpy_src, char *cat_src);
#endif
