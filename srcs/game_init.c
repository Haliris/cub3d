/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:03:43 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/28 17:41:25 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_assets(t_data *data)
{
	int			w;
	int			h;
	t_textdata	*t;

	t = data->textures;
	w = 0;
	h = 0;
	t->text_img[N] = mlx_xpm_file_to_image(data->mlx, t->text_paths[N], &w, &h);
	t->text_img[S] = mlx_xpm_file_to_image(data->mlx, t->text_paths[S], &w, &h);
	t->text_img[E] = mlx_xpm_file_to_image(data->mlx, t->text_paths[E], &w, &h);
	t->text_img[W] = mlx_xpm_file_to_image(data->mlx, t->text_paths[W], &w, &h);
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
