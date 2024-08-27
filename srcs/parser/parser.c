/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:12:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/27 19:32:41 by jteissie         ###   ########.fr       */
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
	{
		data->p_dir_default = NORTH;
		vec_init(&data->p_dir, -1.0f, 0.0f);
	}
	else if (data->map[x][y] == 'S')
	{
		data->p_dir_default = SOUTH;
		vec_init(&data->p_dir, 1.0f, 0.0f);
	}
	else if (data->map[x][y] == 'W')
	{
		data->p_dir_default = WEST;
		vec_init(&data->p_dir, 0.0f, -1.0f);
	}
	else if (data->map[x][y] == 'E')
	{
		data->p_dir_default = EAST;
		vec_init(&data->p_dir, 0.0f, 1.0f);
	}
	vec_init(&data->p_pos, (double)x, (double)y);
}

t_parse_status	verify_map(char **map, t_data *data)
{
	uint32_t	start[2];

	start[0] = 0;
	start[1] = 0;
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

static int	is_element(char *line, t_textdata *textures)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		textures->text_paths[NORTH] = ft_substr(line, 3, ft_strlen(line) - 3);
		if (!textures->text_paths[NORTH])
			return (PANIC);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		textures->text_paths[SOUTH] = ft_substr(line, 3, ft_strlen(line) - 3);
		if (!textures->text_paths[SOUTH])
			return (PANIC);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		textures->text_paths[EAST] = ft_substr(line, 3, ft_strlen(line) - 3);
		if (!textures->text_paths[EAST])
			return (PANIC);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		textures->text_paths[WEST] = ft_substr(line, 3, ft_strlen(line) - 3);
		if (!textures->text_paths[WEST])
			return (PANIC);
	}
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		add_floor_ceiling(line, textures);
	return (SUCCESS);
}

static t_bool	has_all_textures(t_textdata *textures)
{
	size_t	index;

	index = 0;
	while(textures->text_paths[index])
		index++;
	if (index < 4)
		return (FALSE);
	return (TRUE);
}

static int	get_textures_info(t_textdata *textures, int	map_fd)
{
	char	*line;

	line = NULL;

	line = get_next_line(map_fd);
	while (line)
	{
		if (check_element(line, textures) == PANIC)
		{
			free(line);
			return (PANIC);
		}
		free(line);
		line = get_next_line(map_fd);
		if (ft_strncmp(line, "1", 2) == 0 || ft_strncmp(line, "0", 2) == 0)
		{
			free(line);
			break ;
		}
	}
	if (has_all_textures(textures) == FALSE)
		return (PANIC);
	return (SUCCESS);
}

int	parse_map(t_data *data)
{
	data->map = build_map(data);
	if (!data->map)
		return (PANIC);
	get_textures_info(data->textures, data->map_fd);
	if (verify_map(data->map, data) == MAP_ERR)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		return (ft_free_all(data->map), PANIC);
	}
	return (SUCCESS);
}
