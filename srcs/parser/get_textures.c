/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:44:55 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/28 15:56:29 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_atoi_texture(t_textdata *textures, int array[], char *line)
{
	size_t	i;
	size_t	array_i;
	int		value;

	i = 2;
	array_i = 0;
	value = 0;
	while(line[i] && array_i < 3)
	{
		while (line[i] && line[i] != ',' && line[i] != '\n')
		{
			if (ft_isdigit(line[i]) == FALSE)
				return (PANIC);
			value = 10 * value + (line[i++] - '0');
		}
		array[array_i] = value;
		array_i++;
		if (line[i] == ',')
			i++;
		else
			break ;
	}
	if (array_i != 3)
		return (PANIC);
	textures->textures_nb++;
	return (SUCCESS);
}

static int	add_floor_ceiling(char *line, t_textdata *textures)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (ft_atoi_texture(textures, textures->floor, line));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (ft_atoi_texture(textures, textures->ceiling, line));
	return (PANIC);
}

static int	is_element(char *line, t_textdata *textures)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		textures->text_paths[N] = ft_substr(line, 3, ft_strlen(line) - 3);
		if (!textures->text_paths[N])
			return (PANIC);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		textures->text_paths[S] = ft_substr(line, 3, ft_strlen(line) - 3);
		if (!textures->text_paths[S])
			return (PANIC);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		textures->text_paths[E] = ft_substr(line, 3, ft_strlen(line) - 3);
		if (!textures->text_paths[E])
			return (PANIC);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		textures->text_paths[W] = ft_substr(line, 3, ft_strlen(line) - 3);
		if (!textures->text_paths[W])
			return (PANIC);
	}
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (add_floor_ceiling(line, textures));
	else if (ft_strncmp(line, "\n", 2) == 0)
		return (SUCCESS);
	else
		return (PANIC);
	textures->textures_nb++;
	return (SUCCESS);
}

static int	check_textpaths(char **paths)
{
	size_t	index;

	index = 0;
	while (paths[index] != NULL)
		index++;
	if (index != TEXTURES_PATHS)
		return (PANIC);
	return (SUCCESS);
}

static void	panic_clean(t_textdata *textures)
{
	size_t	i;

	i = 0;
	while (textures->text_paths[i])
	{
		free(textures->text_paths[i]);
		i++;
	}
	free(textures);
}

t_textdata	*get_textures_info(char *map_path, t_data *data)
{
	char	*line;
	size_t	line_nb;
	t_textdata	*textures;

	data->map_fd = open(map_path, O_RDONLY);
	if (data->map_fd == -1)
		return (NULL);
	textures = ft_calloc(1, sizeof(t_textdata));
	if (!textures)
		return (NULL);
	line = get_next_line(data->map_fd);
	line_nb = 0;
	while (line)
	{
		if (is_element(line, textures) == PANIC)
		{
			free(line);
			panic_clean(textures);
			return (NULL);
		}
		free(line);
		line = get_next_line(data->map_fd);
		if (ft_strncmp(line, "1", 1) == 0 || ft_strncmp(line, "0", 1) == 0)
		{
			data->map_start = line_nb;
			free(line);
			break ;
		}
		line_nb++;
	}
	if (textures->textures_nb != TEXTURES_NB || check_textpaths(textures->text_paths) == PANIC)
	{
		panic_clean(textures);
		return (NULL);
	}
	return (textures);
}
