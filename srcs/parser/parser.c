/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:12:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/16 15:46:18 by jteissie         ###   ########.fr       */
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

static size_t	get_map_size(char *path)
{
	int		fd;
	size_t	line_nb;
	char	*gnl_buff;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	gnl_buff = get_next_line(fd);
	if (!gnl_buff)
		return (0);
	line_nb = 1;
	while (gnl_buff)
	{
		free(gnl_buff);
		gnl_buff = get_next_line(fd);
		line_nb++;
	}
	close(fd);
	return (line_nb);
}

static char	**build_map(t_data *data)
{
	char			**map;
	char			*line;
	size_t			size;
	uint32_t		index;

	index = 0;
	map = NULL;
	line = get_next_line(data->map_fd);
	if (!line)
		return (NULL);
	size = get_map_size(data->map_path);
	if (size == 0)
	{
		free(line);
		return (NULL);
	}
	map = ft_calloc(size + 1, sizeof(char *));
	if (!map)
		return (NULL);
	while (line)
	{
		map[index] = ft_strdup(line);
		if (!map[index])
		{
			free(line);
			panic_free(map);
			return (NULL);
		}
		free(line);
		line = get_next_line(data->map_fd);
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

int	parse_map(t_data *data)
{
	data->map = build_map(data);
	if (!data->map)
		return (PANIC);
	if (verify_map(data->map) == MAP_ERR)
	{
		ft_putstr_fd("Error, implement custom messages here (parse_map)\n", STDERR_FILENO);
		return (ft_free_all(data->map), PANIC);
	}
	return (SUCCESS);
}
