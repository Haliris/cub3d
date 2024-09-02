/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:51:48 by jteissie          #+#    #+#             */
/*   Updated: 2024/09/02 12:16:14 by tsuchen          ###   ########.fr       */
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
			ft_lstadd_back(&map_list, new_node);
			if (ft_strlen(line) > data->map_width)
				data->map_width = ft_strlen(line);
		}
		else
			free(line);
		line = get_next_line(data->map_fd);
	}
	return (map_list);
}

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
