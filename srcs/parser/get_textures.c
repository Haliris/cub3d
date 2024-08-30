/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:44:55 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/30 11:49:44 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	add_floor_ceiling(char *line, t_textdata *textures)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (ft_atoi_texture(textures, &textures->floor, line));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (ft_atoi_texture(textures, &textures->ceiling, line));
	return (PANIC);
}

static int	is_element(char *line, t_textdata *textures)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (add_info_buff(line, textures, N));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (add_info_buff(line, textures, S));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (add_info_buff(line, textures, E));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (add_info_buff(line, textures, W));
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (add_floor_ceiling(line, textures));
	else if (ft_strncmp(line, "\n", 2) == 0)
		return (SUCCESS);
	else
		return (PANIC);
	return (SUCCESS);
}

static int	parse_info_line(char **line, t_textdata *textures, t_data *data)
{
	while (*line && textures->textures_nb < TEXTURES_NB)
	{
		if (is_element(*line, textures) == PANIC)
		{
			free(*line);
			panic_clean(textures);
			return (PANIC);
		}
		free(*line);
		*line = get_next_line(data->map_fd);
	}
	if (!(*line))
	{
		panic_clean(textures);
		return (PANIC);
	}
	return (SUCCESS);
}

t_textdata	*get_textures_info(t_data *data, char **line)
{
	t_textdata	*textures;

	textures = ft_calloc(1, sizeof(t_textdata));
	if (!textures)
		return (NULL);
	if (parse_info_line(line, textures, data) == PANIC)
		return (NULL);
	if (check_textpaths(textures->text_paths) == PANIC)
	{
		panic_clean(textures);
		return (NULL);
	}
	return (textures);
}
