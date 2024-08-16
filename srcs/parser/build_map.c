/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:51:48 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/16 18:31:34 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static char	**read_map_file(size_t size, char *line, t_data *data)
{
	size_t	index;
	char	**map;

	index = 0;
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

char	**build_map(t_data *data)
{
	char			**map;
	char			*line;
	size_t			size;

	line = get_next_line(data->map_fd);
	if (!line)
		return (NULL);
	size = get_map_size(data->map_path);
	if (size == 0)
		return (free(line), NULL);
	data->map_bound = size;
	map = read_map_file(size, line, data);
	return (map);
}
