/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:22:08 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/30 15:38:09 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	get_curr_dir(t_data *data)
{
	if (data->side == 0)
	{
		if (data->ray_dir.x < 0)
			return (W);
		else
			return (E);
	}
	else
	{
		if (data->ray_dir.y < 0)
			return (N);
		else
			return (S);
	}
}

static void	get_x_coordinate(int *tex_pos, t_data *data, double ray_dist)
{
	double	wall_hit;

	if (data->side == 0)
	{
		wall_hit = data->p_pos.y + ray_dist * data->ray_dir.y;
	}
	else
	{
		wall_hit = data->p_pos.x + ray_dist * data->ray_dir.x;
	}
	wall_hit -= floor(wall_hit);
	tex_pos[0] = (int)(wall_hit * data->textures->tex_w);
	if (tex_pos[0] >= data->textures->tex_w)
		tex_pos[0] = data->textures->tex_w - 1;
}

static void	get_y_coordinate(int *tex_pos, t_data *data, int wall_height, int y)
{
	int	y_scaled;

	y_scaled = y * 256 - HEIGHT * 128 + wall_height * 128;
	tex_pos[1] = ((y_scaled * data->textures->tex_h) / wall_height) / 256;
	if (tex_pos[1] < 0)
		tex_pos[1] = 0;
	if (tex_pos[1] >= data->textures->tex_h)
		tex_pos[1] = data->textures->tex_h - 1;
}

void	mlx_render_wall(t_data *data, int x, int y, double ray_dist)
{
	t_wall		w_data;
	t_textdata	*tex;
	int			color;
	int			dir;
	int			color_index;

	dir = get_curr_dir(data);
	tex = data->textures;
	w_data.height = (int)(HEIGHT / ray_dist);
	w_data.draw_bounds[0] = (HEIGHT - w_data.height) / 2;
	if (w_data.draw_bounds[0] < 0)
		w_data.draw_bounds[0] = 0;
	w_data.draw_bounds[1] = (HEIGHT + w_data.height) / 2;
	if (w_data.draw_bounds[1] >= HEIGHT)
		w_data.draw_bounds[1] = HEIGHT - 1;
	get_x_coordinate(w_data.tex_pos, data, ray_dist);
	get_y_coordinate(w_data.tex_pos, data, w_data.height, y);
	color_index = w_data.tex_pos[1] * tex->tex_w + w_data.tex_pos[0];
	color = ((uint32_t *)tex->text_addr[dir])[color_index];
	rc_mlx_pixel_put(&data->image, x, y, color);
}
