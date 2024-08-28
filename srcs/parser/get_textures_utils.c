/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:29:47 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/28 17:45:22 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_atoi_texture(t_textdata *textures, int array[], char *line)
{
	size_t	i;
	size_t	array_i;
	int		value;

	i = 2;
	array_i = 0;
	value = 0;
	while (line[i] && array_i < 3)
	{
		while (line[i] && line[i] != ',' && line[i] != '\n')
		{
			if (ft_isdigit(line[i]) == FALSE)
				return (PANIC);
			value = 10 * value + (line[i++] - '0');
		}
		array[array_i] = value;
		array_i++;
		if (line[i] != ',')
			break ;
		i++;
	}
	if (array_i != 3)
		return (PANIC);
	textures->textures_nb++;
	return (SUCCESS);
}

int	add_info_buff(char *line, t_textdata *textures, t_texture type)
{
	size_t	i;
	size_t	trim_i;

	i = 0;
	trim_i = ft_strlen(line) - 1;
	if (textures->text_paths[type] != NULL)
		return (PANIC);
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	while (trim_i > 0 && line[trim_i] == ' ')
		trim_i--;
	textures->text_paths[type] = ft_substr(line, i, trim_i - i);
	textures->textures_nb++;
	return (SUCCESS);
}

int	check_textpaths(char **paths)
{
	size_t	index;

	index = 0;
	while (index < TEXTURES_PATHS)
	{
		if (paths[index] == NULL)
			return (PANIC);
		index++;
	}
	return (SUCCESS);
}

void	panic_clean(t_textdata *textures)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (textures->text_paths[i])
			free(textures->text_paths[i]);
		i++;
	}
	free(textures);
}
