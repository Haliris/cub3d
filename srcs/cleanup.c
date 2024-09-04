/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:04:32 by jteissie          #+#    #+#             */
/*   Updated: 2024/09/04 13:17:57 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_textures(t_textdata *textures, void *mlx)
{
	if (textures->text_img[N])
		mlx_destroy_image(mlx, textures->text_img[N]);
	if (textures->text_img[S])
		mlx_destroy_image(mlx, textures->text_img[S]);
	if (textures->text_img[E])
		mlx_destroy_image(mlx, textures->text_img[E]);
	if (textures->text_img[W])
		mlx_destroy_image(mlx, textures->text_img[W]);
	if (textures->text_img[D])
		mlx_destroy_image(mlx, textures->text_img[D]);
	if (textures->text_paths[N])
		free(textures->text_paths[N]);
	if (textures->text_paths[S])
		free(textures->text_paths[S]);
	if (textures->text_paths[E])
		free(textures->text_paths[E]);
	if (textures->text_paths[W])
		free(textures->text_paths[W]);
	if (textures->text_paths[D])
		free(textures->text_paths[D]);
	free(textures);
}

static void	cleanup_frames(t_frame *frames, void *mlx)
{
	t_frame	*tmp;

	while (frames)
	{
		tmp = frames;
		mlx_destroy_image(mlx, frames->img);
		frames = frames->next;
		free(tmp);
	}
}

int	cleanup(t_data *data)
{
	if (data->textures)
		cleanup_textures(data->textures, data->mlx);
	if (data->frames)
		cleanup_frames(data->frames, data->mlx);
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	if (data->mini_map.img)
		mlx_destroy_image(data->mlx, data->mini_map.img);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	panic_free(data->map);
	close(data->map_fd);
	exit(SUCCESS);
}
