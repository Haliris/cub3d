/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:04:51 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/16 14:50:14 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	copy_and_cat(char *out, char *cpy_src, char *cat_src)
{
	int	i;
	int	src_i;

	i = 0;
	src_i = 0;
	while (cpy_src[src_i])
	{
		out[i] = cpy_src[src_i];
		i++;
		src_i++;
	}
	src_i = 0;
	while (cat_src[src_i])
		out[i++] = cat_src[src_i++];
	out[i] = '\0';
}

int	find_eol(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
