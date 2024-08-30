/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:22:08 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/30 15:22:28 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	get_curr_dir(t_data *data)
{
	if (data->side == 0)	{
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

static void get_x_coordinates(int *tex_coordinates, t_data *data, double ray_dist)
{
	double wall_hit;

	if (data->side == 0)
	{
		wall_hit = data->p_pos.y + ray_dist * data->ray_dir.y;
	}
	else
	{
		wall_hit = data->p_pos.x + ray_dist * data->ray_dir.x;
	}

	wall_hit -= floor(wall_hit);
	tex_coordinates[0] = (int)(wall_hit * data->textures->text_width);
	if (tex_coordinates[0] >= data->textures->text_width)
		tex_coordinates[0] = data->textures->text_width - 1;
}

static void get_y_coordinates(int *tex_coordinates, t_data *data, int wall_height, int y)
{
	int d;

	d = y * 256 - HEIGHT * 128 + wall_height * 128;
	tex_coordinates[1] = ((d * data->textures->text_height) / wall_height) / 256;

	if (tex_coordinates[1] < 0)
		tex_coordinates[1] = 0;
	if (tex_coordinates[1] >= data->textures->text_height)
		tex_coordinates[1] = data->textures->text_height - 1;
}

void mlx_render_wall(t_data *data, int x, int y, double ray_dist)
{
	t_wall	wall_data;
	int		color;
	int		dir;
	int		color_index;

	dir = get_curr_dir(data);
	wall_data.height = (int)(HEIGHT / ray_dist);
	wall_data.draw_bounds[0] = (HEIGHT - wall_data.height) / 2;
	if (wall_data.draw_bounds[0] < 0)
		wall_data.draw_bounds[0] = 0;
	wall_data.draw_bounds[1] = (HEIGHT + wall_data.height) / 2;
	if (wall_data.draw_bounds[1] >= HEIGHT)
		wall_data.draw_bounds[1] = HEIGHT - 1;
	get_x_coordinates(wall_data.tex_coordinates, data, ray_dist);
	get_y_coordinates(wall_data.tex_coordinates, data, wall_data.height, y);
	color_index = wall_data.tex_coordinates[1] * data->textures->text_width + wall_data.tex_coordinates[0];
	color = ((uint32_t *)data->textures->text_addr[dir])[color_index];
	rc_mlx_pixel_put(&data->image, x, y, color);
}
