/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:04:32 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/27 17:04:48 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_textures(void *textures)
{
	if (textures[NORTH])
		mlx_destroy_image(textures[NORTH]);
	if (textures[SOUTH])
		mlx_destroy_image(textures[SOUTH]);
	if (textures[EAST])
		mlx_destroy_image(textures[EAST]);
	if (textures[WEST])
		mlx_destroy_image(textures[WEST]);
}

void	cleanup(t_data *data)
{
	cleanup_textures(data->texture);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
		free(data->mlx);
	mlx_destroy_display(data->mlx);
}
