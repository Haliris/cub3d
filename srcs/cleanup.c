/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:04:32 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/27 18:53:08 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_textures(t_textdata *textures)
{
	if (textures->text_img[NORTH])
		mlx_destroy_image(textures->text_img[NORTH]);
	if (textures->text_img[SOUTH])
		mlx_destroy_image(textures->text_img[SOUTH]);
	if (textures->text_img[EAST])
		mlx_destroy_image(textures->text_img[EAST]);
	if (textures->text_img[WEST])
		mlx_destroy_image(textures->text_img[WEST]);
	free(textures);
}

void	cleanup(t_data *data)
{
	if (data->textures)
		cleanup_textures(data->texture);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
		free(data->mlx);
	mlx_destroy_display(data->mlx);
}
