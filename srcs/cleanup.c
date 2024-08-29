/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:04:32 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/29 17:45:39 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_textures(t_textdata *textures, void *mlx)
{
	if (textures->text_paths[N])
		free(textures->text_paths[N]);
	if (textures->text_paths[S])
		free(textures->text_paths[S]);
	if (textures->text_paths[E])
		free(textures->text_paths[E]);
	if (textures->text_paths[W])
		free(textures->text_paths[W]);
	if (textures->text_img[N])
		mlx_destroy_image(textures->text_img[N], mlx);
	if (textures->text_img[S])
		mlx_destroy_image(textures->text_img[S], mlx);
	if (textures->text_img[E])
		mlx_destroy_image(textures->text_img[E], mlx);
	if (textures->text_img[W])
		mlx_destroy_image(textures->text_img[W], mlx);
	free(textures);
}

int	cleanup(t_data *data)
{
	if (data->textures)
		cleanup_textures(data->textures, data->mlx);
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(SUCCESS);
}
