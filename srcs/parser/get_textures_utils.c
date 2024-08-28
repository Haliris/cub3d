/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:29:47 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/28 18:28:18 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// int	ft_atoi_texture(t_textdata *textures, int array[], char *line)
// {
// 	size_t	i;
// 	size_t	array_i;
// 	int		value;

// 	i = 2;
// 	array_i = 0;
// 	value = 0;
// 	while (line[i] && array_i < 3)
// 	{
// 		while (line[i] && line[i] != ',' && line[i] != '\n')
// 		{
// 			if (ft_isdigit(line[i]) == FALSE)
// 				return (PANIC);
// 			value = 10 * value + (line[i++] - '0');
// 		}
// 		array[array_i] = value;
// 		array_i++;
// 		if (line[i] != ',')
// 			break ;
// 		i++;
// 	}
// 	if (array_i != 3)
// 		return (PANIC);
// 	textures->textures_nb++;
// 	return (SUCCESS);
// }


int	ft_atoi_texture(t_textdata *textures, int array[], char *line)
{
	size_t	i = 2;
	size_t	array_i = 0;

	while (line[i] && line[i] != '\n' && array_i < 3)
	{
		while (line[i] == ' ')
			i++;
		if (ft_isdigit(line[i]))
		{
			while (ft_isdigit(line[i]))
			{
				array[array_i] = 10 * array[array_i] + (line[i++] - '0');
				if (array[array_i] > 255)
					return (PANIC);
			}
			array_i++;
		}
		else
			return (PANIC);
		while (line[i] == ' ')
			i++;
		if (line[i] && (line[i] != ',' && (array_i != 3 && line[i] == '\n')))
			return (PANIC);
		i++;
	}
	if (array_i != 3)
		return (PANIC);
	if (line[i] != '\0')
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
