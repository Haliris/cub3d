/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:03:43 by jteissie          #+#    #+#             */
/*   Updated: 2024/09/02 17:25:27 by jteissie         ###   ########.fr       */
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
	t->text_addr[D] = mlx_get_data_addr(t->text_img[D], &pb, &lb, &endian);
}

static int	load_assets(t_data *data)
{
	t_textdata	*t;
	char		**p;
	void		*m;

	t = data->textures;
	p = t->text_paths;
	m = data->mlx;
	t->text_img[W] = mlx_xpm_file_to_image(m, p[W], &t->tex_h[W], &t->tex_w[W]);
	t->text_img[S] = mlx_xpm_file_to_image(m, p[S], &t->tex_h[S], &t->tex_w[S]);
	t->text_img[E] = mlx_xpm_file_to_image(m, p[E], &t->tex_h[E], &t->tex_w[E]);
	t->text_img[N] = mlx_xpm_file_to_image(m, p[N], &t->tex_h[N], &t->tex_w[N]);
	t->text_img[D] = mlx_xpm_file_to_image(m, p[D], &t->tex_h[D], &t->tex_w[D]);
	if (!t->text_img[N] || !t->text_img[S]
		|| !t->text_img[W] || !t->text_img[E]
		|| !t->text_img[D])
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
		ft_putstr_fd("Error when opening window\n", ER);
		cleanup(data);
		return (PANIC);
	}
	if (load_assets(data) == PANIC)
	{
		ft_putstr_fd("Error when loading assets\n", ER);
		cleanup(data);
		return (PANIC);
	}
	data->image.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp,
			&data->image.line_length, &data->image.endian);
	data->mini_map.img = mlx_new_image(data->mlx, MINI_MAP_W, MINI_MAP_H);
	data->mini_map.addr = mlx_get_data_addr(data->mini_map.img,
			&data->mini_map.bpp, &data->mini_map.line_length,
			&data->mini_map.endian);
	return (SUCCESS);
}
