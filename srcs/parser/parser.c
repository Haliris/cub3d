/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:12:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/30 14:09:41 by tsuchen          ###   ########.fr       */
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
		vec_init(&data->p_dir, -1.0f, 0.0f);
		vec_init(&data->p_cam, 0.0f, tan(FOV / 2));
	}
	else if (data->map[x][y] == 'S')
	{
		vec_init(&data->p_dir, 1.0f, 0.0f);
		vec_init(&data->p_cam, 0.0f, tan(FOV / 2) * -1);
	}
	else if (data->map[x][y] == 'W')
	{
		vec_init(&data->p_dir, 0.0f, -1.0f);
		vec_init(&data->p_cam, tan(FOV / 2) * -1, 0.0f);
	}
	else if (data->map[x][y] == 'E')
	{
		vec_init(&data->p_dir, 0.0f, 1.0f);
		vec_init(&data->p_cam, tan(FOV / 2), 0.0f);
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

int	parse_map(t_data *data)
{
	char	*line;

	line = get_next_line(data->map_fd);
	if (!line)
		return (PANIC);
	data->textures = get_textures_info(data, &line);
	if (!data->textures)
	{
		if (line)
			free(line);
		close(data->map_fd);
		ft_putstr_fd("Error\n", STDERR_FILENO);
		return (PANIC);
	}
	data->map = build_map(data, line);
	close(data->map_fd);
	if (!data->map)
		return (PANIC);
	if (verify_map(data->map, data) == MAP_ERR)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		return (ft_free_all(data->map), PANIC);
	}
	return (SUCCESS);
}

// void	print_parsed_map(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	printf("textures\n");
// 	while (i < 4)
// 	{
// 		printf("text_paths %d is %s\n", i, data->textures->text_paths[i]);
// 		printf("text_addr %d is %s\n", i, data->textures->text_addr[i]);
// 		i++;
// 	}
// 	printf("text floor is %d\n", data->textures->floor);
// 	printf("text ceiling is %d\n", data->textures->ceiling);
// 	i = 0;
// 	while (data->map[i])
// 	{
// 		printf("%s", data->map[i]);
// 		i++;
// 	}
// }
