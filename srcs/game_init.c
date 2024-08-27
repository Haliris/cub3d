/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:03:43 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/27 17:05:59 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_assets(t_data *data)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	data->textures[NORTH] = mlx_xpm_file_to_image(data->mlx, TEXTURE_NORTH, &width, &height);
	data->textures[SOUTH] = mlx_xpm_file_to_image(data->mlx, TEXTURE_SOUTH, &width, &height);
	data->textures[EAST] = mlx_xpm_file_to_image(data->mlx, TEXTURE_EAST, &width, &height);
	data->textures[WEST] = mlx_xpm_file_to_image(data->mlx, TEXTURE_WEST, &width, &height);
	if (!data->textures[NORTH] || !data->textures[SOUTH] || !data->textures[WEST] || !data->textures[EAST])
		return (PANIC);
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
