/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:22:08 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/29 17:08:54 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	get_current_dir(t_data *data)
{
	if (data->ray_dir.y < 0)
		return (N)
	else if (data->ray_dir.x < 0)
		return (W)
	else if (data->ray_dir.y >= 0)
		return (S)
	else if (data->ray_dir.x >= 0)
		return (E)
}

static void	get_tex_coordinates(int *tex_coordinates, t_data *data, int wall_height, double ray_dist)
{
	double	wall_x;

	if (data->side == 0)
		wall_x = data->p_pos.y + ray_dist * data->ray_dir.y;
	else
		wall_x = data->p_pos.x + ray_dist * data->ray.dir.x;
	wall_x -= floor(wall_x);
	tex_coordinates[0] = (int)(wall_x * (double)data->textures->text_width)
	if (tex_coordinates[0] >= data->textures->text_width)
		tex_coordinates[0] = data->tex_width - 1;
	tex_coordinates[1] = ((y - data->wall_data.draw_bounds[0]) * data->textures->height) / wall_height;
	if (tex_coordinates[1] >= data->textures->text_height)
		tex_coordinates[1] = data->textures->text_height - 1;
}

void	mlx_render_wall(t_data *data, int x, int y, double ray_dist)
{
	t_wall	wall_data;
	int		color;
	int		dir;

	dir = get_curr_dir(data);
	wall_data = data->wall_data;
	wall_data.height = (int)(HEIGHT / ray_dist);
	wall_data.draw_bounds[0] = (HEIGHT - wall_data.height) / 2;
	if (wall_data.draw_bounds[0] < 0)
		wall_data.draw_bounds[0] = 0;
	wall_data.draw_bounds[1] = (HEIGHT + wall_data.wall_height) / 2;
	if (wall_data.draw_bounds[1] >= HEIGHT)
		wall_data.draw_bounds[1] = HEIGHT - 1;
	get_tex_coordinates(wall_data.tex_coordinates, data, wall_data.height, ray_dist)
	color = data->textures->text_addr[dir][wall_data.tex_coordinates[1] * data->textures->width + wall_data.tex_coordinates[0]];
	rc_mlx_pixel_put(data->image, x, y, color);
}
