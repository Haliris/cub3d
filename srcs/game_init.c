/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:03:43 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/30 15:40:55 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_text_addr(t_textdata *t)
{
	int	pb;
	int	lb;
	int	endian;

	t->text_addr[N] = mlx_get_data_addr(t->text_img[N], &pb, &lb, &endian);
	t->text_addr[S] = mlx_get_data_addr(t->text_img[S], &pb, &lb, &endian);
	t->text_addr[W] = mlx_get_data_addr(t->text_img[W], &pb, &lb, &endian);
	t->text_addr[E] = mlx_get_data_addr(t->text_img[E], &pb, &lb, &endian);
}

static int	load_assets(t_data *data)
{
	t_textdata	*t;
	char		**path;
	void		*mlx;

	t = data->textures;
	path = t->text_paths;
	mlx = data->mlx;
	t->text_img[N] = mlx_xpm_file_to_image(mlx, path[N], &t->tex_h, &t->tex_w);
	t->text_img[S] = mlx_xpm_file_to_image(mlx, path[S], &t->tex_h, &t->tex_w);
	t->text_img[E] = mlx_xpm_file_to_image(mlx, path[E], &t->tex_h, &t->tex_w);
	t->text_img[W] = mlx_xpm_file_to_image(mlx, path[W], &t->tex_h, &t->tex_w);
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
