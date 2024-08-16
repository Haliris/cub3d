/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:00:57 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/16 14:22:57 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3d.h"

typedef enum e_parse_status
{
	MAP_OK,
	MAP_ERR,
	PANIC_ERR,
}	t_parse_status;

int	parse_map(int map_fd);

#endif
