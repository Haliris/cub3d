/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:12:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/15 18:03:39 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 1 are walls, 0 are walkable spaces, whitespaces are walkable spaces. Map is invalid if no walkable spaces or not enclosed by walls

static char	**build_map(int map_fd)
{
	char			**map;
	char			*line;
	u_int16_t		index;

	index = 0;
	line = get_next_line(map_fd);
	if (!line)
		return (NULL);
	while (line)
	{
		map[index] == ft_calloc(1, sizeof(char *));
		if (!map[index])
		{
			free(line);
			panic_free(map);
			return (NULL);
		}
		map[index] = line;
		line = get_next_line(map_fd);
		index++;
	}
	map[index] = NULL;
	return (map);
}

static int	find_start(u_int16_t *coordinates, char **map)
{
	u_int16_t	x;
	u_int16_t	y;

	x = 0;
	y = 0;
	coordinates[0] = -1;
	coordinates[1] = -1;
	while (map[x][y])
	{
		while (map[x][y])
		{
			if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'W' || map[x][y] == 'E') //enums please
			{
				if (coordinates[0] != -1 || coordinates[1] != 1)
					return (PANIC);
				coordinates[0] = x;
				coordinates[1] = y;
			}
			y++;
		}
		x++;
		y = 0;
	}
	if (coordinates[0] == -1)
		return (PANIC);
	return (SUCCESS);
}


t_bool	is_invalid_char(char c)
{
	if (c == '1' || c == '0')
		return (FALSE);
	else if (c == ' ')
		return (FALSE);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (FALSE);
	return (TRUE);
}

int	check_invalid_chars(char **map)
{
	u_int16_t	x;
	u_int16_t	y;

	x = 0;
	y = 0;
	while (map[x][y])
	{
		while (map[x][y])
		{
			if (is_invalid_char(map[x][y]) == TRUE)
				return (PANIC);
			y++;
		}
		x++;
		y = 0;
	}
	return (SUCCESS);
}

void	fill_whitespaces(char **map)
{
	u_int16_t	x;
	u_int16_t	y;

	x = 0;
	y = 0;
	while (map[x][y])
	{
		while (map[x][y])
		{
			if (map[x][y] == ' ')
				map[x][y] == '1';
			y++;
		}
		x++;
		y = 0;
	}
}

int	check_walls(char **map)
{
	u_int16_t	x;
	u_int16_t	y;
	char		**control;

	control = dup_array(map);
	if (!control)
		return (PANIC);
	x = 0;
	y = 0;
	while ()
	{

	}
}

int	verify_map(char **map)
{
	u_int16_t	start[2];

	if (check_invalid_chars(map) == PANIC)
		return (PANIC);
	if (find_start(&start, map) == PANIC)
		return (PANIC);
	fill_whitespaces(map);
	if (check_walls(map) == PANIC)
		return (PANIC);
	if (error)
		return (MAP_ERR);
	return (SUCCESS);
}

int	parse_map(int map_fd)
{
	char	**map;

	map = build_map(map_fd);
	if (!map)
		return (ft_free(map), PANIC);
	if (verify_map(map) == MAP_ERR)
		return (ft_free(map), PANIC);
}
