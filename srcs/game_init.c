/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:03:43 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/28 14:24:57 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_assets(t_data *data)
{
	int			width;
	int			height;
	t_textdata	*textures;

	textures = data->textures;
	width = 0;
	height = 0;
	textures->text_img[N] = mlx_xpm_file_to_image(data->mlx, textures->text_paths[N], &width, &height);
	textures->text_img[S] = mlx_xpm_file_to_image(data->mlx, textures->text_paths[S], &width, &height);
	textures->text_img[E] = mlx_xpm_file_to_image(data->mlx,textures->text_paths[E], &width, &height);
	textures->text_img[W] = mlx_xpm_file_to_image(data->mlx,textures->text_paths[W], &width, &height);
	if (!textures->text_img[N] || !textures->text_img[S]
		|| !textures->text_img[W] || !textures->text_img[E])
	{
		free(textures);
		return (PANIC);
	}
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
