/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:29:47 by jteissie          #+#    #+#             */
/*   Updated: 2024/09/04 13:59:11 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	convert_nb(char *str, int *array, size_t *array_i, size_t *i)
{
	int	nb;

	nb = 0;
	while (ft_isdigit(str[*i]))
	{
		nb = 10 * nb + (str[*i] - '0');
		array[*array_i] = nb;
		if (array[*array_i] > 255)
			return (PANIC);
		*i = *i + 1;
	}
	*array_i = *array_i + 1;
	return (SUCCESS);
}

int	ft_atoi_texture(t_textdata *textures, int *color, char *line)
{
	size_t	i;
	size_t	array_i;
	int		rgb[3];

	i = 2;
	array_i = 0;
	while (line[i] && line[i] != '\n' && array_i < 3)
	{
		while (line[i] == ' ')
			i++;
		if (ft_isdigit(line[i]))
			convert_nb(line, rgb, &array_i, &i);
		else
			return (PANIC);
		while (line[i] == ' ')
			i++;
		if (line[i] && (line[i] != ',' && (array_i != 3 && line[i] == '\n')))
			return (PANIC);
		i++;
	}
	if (array_i != 3 || line[i] != '\0')
		return (PANIC);
	textures->textures_nb++;
	*color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
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
	while (i < TEXTURES_PATHS)
	{
		if (textures->text_paths[i])
			free(textures->text_paths[i]);
		i++;
	}
	free(textures);
}
