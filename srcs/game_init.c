/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:03:43 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/30 14:38:33 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_text_addr(t_textdata *t)
{
	int	pixel_bits;
	int	line_bytes;
	int	endian;

	t->text_addr[N] = mlx_get_data_addr(t->text_img[N], &pixel_bits, &line_bytes, &endian);
	t->text_addr[S] = mlx_get_data_addr(t->text_img[S], &pixel_bits, &line_bytes, &endian);
	t->text_addr[W] = mlx_get_data_addr(t->text_img[W], &pixel_bits, &line_bytes, &endian);
	t->text_addr[E] = mlx_get_data_addr(t->text_img[E], &pixel_bits, &line_bytes, &endian);
}

static int	load_assets(t_data *data)
{
	t_textdata	*t;

	t = data->textures;
	t->text_img[N] = mlx_xpm_file_to_image(data->mlx, t->text_paths[N], &t->text_height, &t->text_width);
	t->text_img[S] = mlx_xpm_file_to_image(data->mlx, t->text_paths[S], &t->text_height, &t->text_width);
	t->text_img[E] = mlx_xpm_file_to_image(data->mlx, t->text_paths[E], &t->text_height, &t->text_width);
	t->text_img[W] = mlx_xpm_file_to_image(data->mlx, t->text_paths[W], &t->text_height, &t->text_width);
	if (!t->text_img[N] || !t->text_img[S]
		|| !t->text_img[W] || !t->text_img[E])
		return (PANIC);
	get_text_addr(t);
	return (SUCCESS);
}

int	game_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (PANIC);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, P_NAME);
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
	data->image.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp,
			&data->image.line_length, &data->image.endian);
	return (SUCCESS);
}
