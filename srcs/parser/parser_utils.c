/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:12:37 by jteissie          #+#    #+#             */
/*   Updated: 2024/09/04 14:13:09 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	is_invalid_char(char c)
{
	if (c == '1' || c == '0')
		return (FALSE);
	else if (c == ' ' || c == '\n')
		return (FALSE);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'D')
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
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

t_parse_status	find_start(int coordinate[], char **map)
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
				if (coordinate[0] != -1 || coordinate[1] != -1)
					return (MAP_ERR);
				coordinate[0] = x;
				coordinate[1] = y;
			}
			y++;
		}
		y = 0;
		x++;
	}
	if (coordinate[0] == -1 && coordinate[1] == -1)
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
