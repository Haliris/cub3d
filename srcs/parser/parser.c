/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:12:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/16 14:42:13 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 1 are walls, 0 are walkable spaces, whitespaces are walkable spaces. Map is invalid if no walkable spaces or not enclosed by walls

static void	panic_free(char **array)
{
	u_int32_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**build_map(int map_fd)
{
	char			**map;
	char			*line;
	uint32_t		index;

	index = 0;
	map = ft_calloc(1, sizeof(char **));
	if (!map)
		return (NULL);
	line = get_next_line(map_fd);
	if (!line)
		return (NULL);
	while (line)
	{
		map[index] = ft_calloc(1, sizeof(char *));
		if (!map[index])
		{
			free(line);
			panic_free(map);
			return (NULL);
		}
		map[index] = line;
		free(line);
		line = get_next_line(map_fd);
		index++;
	}
	map[index] = NULL;
	return (map);
}

static t_parse_status	find_start(uint32_t coordinates[], char **map)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	coordinates[0] = 0;
	coordinates[1] = 0;
	while (map[x][y])
	{
		while (map[x][y])
		{
			if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'W' || map[x][y] == 'E') //enums please
			{
				if (coordinates[0] != 0 || coordinates[1] != 0)
					return (MAP_ERR);
				coordinates[0] = x;
				coordinates[1] = y;
			}
			y++;
		}
		x++;
		y = 0;
	}
	if (coordinates[0] == 0 && (map[0][0] == '0' || map[0][0] == '1'))
		return (MAP_ERR);
	return (MAP_OK);
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

t_parse_status	check_invalid_chars(char **map)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (map[x][y])
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
	while (map[x][y])
	{
		while (map[x][y])
		{
			if (map[x][y] == ' ')
				map[x][y] = '1';
			y++;
		}
		x++;
		y = 0;
	}
}

t_parse_status	check_walls(char **map, uint32_t x, uint32_t y)
{
	if (map[x][y] == '1')
		return (MAP_OK);
	else if (map[x][y] == '\n' || x == 0 || map[x] == NULL)
		return (MAP_ERR);
	else if (map[x][y] == '\0' || y == 0)
		return (MAP_ERR);
	if (check_walls(map, x - 1, y) == MAP_ERR)
		return (MAP_ERR);
	if (check_walls(map, x + 1, y) == MAP_ERR)
		return (MAP_ERR);
	if (check_walls(map, x, y - 1) == MAP_ERR)
		return (MAP_ERR);
	if (check_walls(map, x, y + 1) == MAP_ERR)
		return (MAP_ERR);
	return (MAP_OK);
}

t_parse_status	verify_map(char **map)
{
	uint32_t	start[2];

	if (check_invalid_chars(map) == MAP_ERR)
		return (MAP_ERR);
	fill_whitespaces(map);
	if (find_start(start, map) == MAP_ERR)
		return (MAP_ERR);
	if (check_walls(map, start[0], start[1]) == MAP_ERR)
		return (MAP_ERR);
	return (MAP_OK);
}

int	parse_map(int map_fd)
{
	char	**map;

	map = build_map(map_fd);
	if (!map)
		return (PANIC);
	if (verify_map(map) == MAP_ERR)
	{
		ft_putstr_fd("Error, implement custom messages here (parse_map)\n", STDERR_FILENO);
		return (ft_free_all(map), PANIC);
	}
	return (SUCCESS);
}
