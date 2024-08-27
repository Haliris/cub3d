/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:03:43 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/27 18:22:47 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_assets(t_data *data)
{
	int			width;
	int			height;
	t_textdata	*textures;

	width = 0;
	height = 0;
	textures = ft_calloc(1, sizeof(t_textdata));
	if (!textures)
		return (PANIC);
	textures->text_img[NORTH] = mlx_xpm_file_to_image(data->mlx, TEXTURE_NORTH, &width, &height);
	textures->text_img[SOUTH] = mlx_xpm_file_to_image(data->mlx, TEXTURE_SOUTH, &width, &height);
	textures->text_img[EAST] = mlx_xpm_file_to_image(data->mlx, TEXTURE_EAST, &width, &height);
	textures->text_img[WEST] = mlx_xpm_file_to_image(data->mlx, TEXTURE_WEST, &width, &height);
	if (!textures->text_img[NORTH] || !textures->text_img[SOUTH]
		|| !textures->text_img[WEST] || !textures->text_img[EAST])
	{
		free(textures);
		return (PANIC);
	}
	data->textures = textures;
	return (SUCCESS);
}

int	game_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (PANIC);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	if (!data->window)
	{
		cleanup(data);
		return (PANIC);
	}
	if (load_assets(data) == PANIC)
	{
		cleanup(data);
		return (PANIC);
	}
	return (SUCCESS);
}
