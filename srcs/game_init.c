/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:03:43 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/29 15:48:24 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_assets(t_data *data)
{
	t_textdata	*t;

	t = data->textures;
	t->text_img[N] = mlx_xpm_file_to_image(data->mlx, t->text_paths[N], t->text_height, t->text_width);
	t->text_img[S] = mlx_xpm_file_to_image(data->mlx, t->text_paths[S], t->text_height, t->text_width);
	t->text_img[E] = mlx_xpm_file_to_image(data->mlx, t->text_paths[E], t->text_height, t->text_width);
	t->text_img[W] = mlx_xpm_file_to_image(data->mlx, t->text_paths[W], t->text_height, t->text_width);
	if (!t->text_img[N] || !t->text_img[S]
		|| !t->text_img[W] || !t->text_img[E])
		return (PANIC);
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
