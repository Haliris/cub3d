/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:12:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/27 13:17:50 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parse_status	check_walls(char **map, uint32_t x, uint32_t y, size_t bound)
{
	if (x == bound || y >= ft_strlen(map[x]))
		return (MAP_ERR);
	else if (map[x][y] == 'F')
		return (MAP_OK);
	else if (map[x][y] == '1')
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

	start[0] = -1;
	start[1] = -1;
	if (check_invalid_chars(map) == MAP_ERR)
		return (MAP_ERR);
	fill_whitespaces(map);
	if (find_start(start, map) == MAP_ERR)
		return (MAP_ERR);
	get_player_dir(data, start[0], start[1]);
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
		ft_putstr_fd("Error\n", STDERR_FILENO);
		return (ft_free_all(data->map), PANIC);
	}
	return (SUCCESS);
}
