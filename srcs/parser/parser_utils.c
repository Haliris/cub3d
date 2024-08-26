/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:12:37 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/26 15:47:38 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	is_invalid_char(char c)
{
	if (c == '1' || c == '0')
		return (FALSE);
	else if (c == ' ' || c == '\n')
		return (FALSE);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (FALSE);
	return (TRUE);
}

t_parse_status	check_invalid_chars(char **map)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (map[x])
	{
		while (map[x][y])
		{
			if (is_invalid_char(map[x][y]) == TRUE)
				return (MAP_ERR);
			y++;
		}
		x++;
		y = 0;
	}
	return (MAP_OK);
}

void	fill_whitespaces(char **map)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (map[x])
	{
		while (map[x][y])
		{
			if (map[x][y] == ' ')
				map[x][y] = '1';
			y++;
		}
		y = 0;
		x++;
	}
}

static uint32_t	is_cardinal_pos(char c)
{
	return (c == NORTH || c == SOUTH || c == WEST || c == EAST);
}

t_parse_status	find_start(uint32_t coordinates[], char **map)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (map[x])
	{
		while (map[x][y])
		{
			if (is_cardinal_pos(map[x][y]))
			{
				if (coordinates[0] != 0 || coordinates[1] != 0)
					return (MAP_ERR);
				coordinates[0] = x;
				coordinates[1] = y;
			}
			y++;
		}
		y = 0;
		x++;
	}
	if (coordinates[0] == 0 && (!is_cardinal_pos(map[0][0])))
		return (MAP_ERR);
	return (MAP_OK);
}

// static void	print_map(char **map)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (map[x])
// 	{
// 		while (map[x][y])
// 		{
// 			ft_putchar_fd(map[x][y], STDOUT_FILENO);
// 			y++;
// 		}
// 		y = 0;
// 		x++;
// 	}
// }
