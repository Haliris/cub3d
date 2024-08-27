/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:00:57 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/27 14:00:34 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

typedef enum e_bool		t_bool;
typedef struct s_data	t_data;

typedef enum e_parse_status
{
	MAP_OK,
	MAP_ERR,
	PANIC_ERR,
}	t_parse_status;

int				parse_map(t_data *data);
char			**build_map(t_data *data);
t_bool			is_invalid_char(char c);
t_parse_status	check_invalid_chars(char **map);
void			fill_whitespaces(char **map);
t_parse_status	find_start(uint32_t coordinates[], char **map);
#endif
