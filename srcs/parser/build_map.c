/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:51:48 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/30 12:00:04 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	panic_free(char **array)
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

// static size_t	get_map_size(char *path)
// {
// 	int		fd;
// 	size_t	line_nb;
// 	char	*gnl_buff;

// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		return (0);
// 	gnl_buff = get_next_line(fd);
// 	if (!gnl_buff)
// 		return (0);
// 	line_nb = 1;
// 	while (gnl_buff)
// 	{
// 		free(gnl_buff);
// 		gnl_buff = get_next_line(fd);
// 		line_nb++;
// 	}
// 	close(fd);
// 	return (line_nb);
// }

static t_list	*read_map_file(char *line, t_data *data)
{
	t_list	*map_list;
	t_list	*new_node;

	map_list = NULL;
	while (line)
	{
		if (strncmp(line, "\n", 1))
		{
			new_node = ft_lstnew(line);
			if (!new_node)
			{
				free(line);
				ft_lstclear(&map_list, free);
				return (NULL);
			}
			ft_lstadd_back(&map_list, ft_lstnew(line));
		}
		else
			free(line);
		line = get_next_line(data->map_fd);
	}
	return (map_list);
}

// static char	**read_map_file(size_t size, char *line, t_data *data)
// {
// 	size_t	index;
// 	char	**map;

// 	index = 0;
// 	map = ft_calloc(size + 1, sizeof(char *));
// 	if (!map)
// 		return (NULL);
// 	while (line)
// 	{
// 		map[index] = ft_strdup(line);
// 		if (!map[index])
// 		{
// 			free(line);
// 			panic_free(map);
// 			return (NULL);
// 		}
// 		free(line);
// 		line = get_next_line(data->map_fd);
// 		index++;
// 	}
// 	map[index] = NULL;
// 	return (map);
// }

char	**build_map(t_data *data, char *line)
{
	t_list	*map_list;
	char	**map;
	t_list	*tmp;
	size_t	i;

	if (!line)
		return (NULL);
	map_list = read_map_file(line, data);
	if (!map_list)
		return (NULL);
	data->map_bound = ft_lstsize(map_list);
	map = ft_calloc(ft_lstsize(map_list) + 1, sizeof(char *));
	if (!map)
		return (ft_lstclear(&map_list, free), NULL);
	tmp = map_list;
	i = 0;
	while (tmp)
	{
		map[i++] = (char *)tmp->content;
		tmp = tmp->next;
	}
	map[i] = NULL;
	ft_lstclear_1(&map_list);
	return (map);
}
