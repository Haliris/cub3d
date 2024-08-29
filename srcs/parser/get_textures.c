/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:44:55 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/29 20:03:29 by tsuchen          ###   ########.fr       */
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

static int	parse_info_line(char *line, t_textdata *textures, t_data *data)
{
	// size_t	line_nb;

	// line_nb = 0;
	while (line && textures->textures_nb < TEXTURES_NB)
	{
		if (is_element(line, textures) == PANIC)
		{
			free(line);
			panic_clean(textures);
			return (PANIC);
		}
		free(line);
		line = get_next_line(data->map_fd);
		// if (ft_strncmp(line, "1", 1) == 0 || ft_strncmp(line, "0", 1) == 0)
		// {
		// 	data->map_start = line_nb;
		// 	free(line);
		// 	break ;
		// }
		// line_nb++;
	}
	if (!line)
	{
		panic_clean(textures);
		return (PANIC);
	}
	return (SUCCESS);
}

t_textdata	*get_textures_info(t_data *data, char *line)
{
	t_textdata	*textures;

	// data->map_fd = open(map_path, O_RDONLY);
	// if (data->map_fd == -1)
	// 	return (NULL);
	textures = ft_calloc(1, sizeof(t_textdata));
	if (!textures)
		return (NULL);
	// line = get_next_line(data->map_fd);
	if (parse_info_line(line, textures, data) == PANIC)
		return (NULL);
	if (check_textpaths(textures->text_paths) == PANIC)
	{
		panic_clean(textures);
		return (NULL);
	}
	return (textures);
}
