/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:12:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/16 16:58:07 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_parse_status	find_start(uint32_t coordinates[], char **map)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	coordinates[0] = 0;
	coordinates[1] = 0;
	while (map[x])
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
		y = 0;
		x++;
	}
	if (coordinates[0] == 0 && (map[0][0] == '0' || map[0][0] == '1'))
		return (MAP_ERR);
	return (MAP_OK);
}

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

t_parse_status	check_walls(char **map, uint32_t x, uint32_t y, size_t bound)
{
	if (map[x][y] == 'F')
		return (MAP_OK);
	if (y >= ft_strlen(map[x]) || x >= bound)
		return (MAP_ERR);
	if (map[x][y] == '1')
		return (MAP_OK);
	else if (x == 0 || map[x] == NULL)
		return (MAP_ERR);
	else if (y == 0 || map[x][y] == '\n' || map[x][y] == '\0')
		return (MAP_ERR);
	map[x][y] = 'F';
	if (check_walls(map, x - 1, y, bound) == MAP_ERR)
		return (MAP_ERR);
	if (check_walls(map, x + 1, y, bound) == MAP_ERR)
		return (MAP_ERR);
	if (check_walls(map, x, y - 1, bound) == MAP_ERR)
		return (MAP_ERR);
	if (check_walls(map, x, y + 1, bound) == MAP_ERR)
		return (MAP_ERR);
	return (MAP_OK);
}

static void	get_player_dir(t_data *data, u_int32_t x, u_int32_t y)
{
	if (data->map[x][y] == 'N')
		data->p_dir = NORTH;
	else if (data->map[x][y] == 'S')
		data->p_dir = SOUTH;
	else if (data->map[x][y] == 'W')
		data->p_dir = WEST;
	else if (data->map[x][y] == 'E')
		data->p_dir = EAST;
}

t_parse_status	verify_map(char **map, t_data *data)
{
	uint32_t	start[2];

	if (check_invalid_chars(map) == MAP_ERR)
		return (MAP_ERR);
	get_player_dir(data, start[0], start[1]);
	fill_whitespaces(map);
	if (find_start(start, map) == MAP_ERR)
		return (MAP_ERR);
	if (check_walls(map, start[0], start[1], data->map_bound) == MAP_ERR)
		return (MAP_ERR);
	return (MAP_OK);
}

int	parse_map(t_data *data)
{
	data->map = build_map(data);
	if (!data->map)
		return (PANIC);
	if (verify_map(data->map, data) == MAP_ERR)
	{
		ft_putstr_fd("Error, implement custom messages here (parse_map)\n", STDERR_FILENO);
		return (ft_free_all(data->map), PANIC);
	}
	return (SUCCESS);
}
