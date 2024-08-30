/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:22:08 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/30 14:44:35 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	get_curr_dir(t_data *data)
{
	if (data->side == 0) // Vertical wall
	{
		if (data->ray_dir.x < 0)
			return (W); // West
		else
			return (E); // East
	}
	else // Horizontal wall
	{
		if (data->ray_dir.y < 0)
			return (N); // North
		else
			return (S); // South
	}
}

static void	get_x_coordinates(int *tex_coordinates, t_data *data, double ray_dist)
{
    double wall_hit_x, wall_hit_y;
    int map_x, map_y;

    // Calculate the world coordinates of where the ray hits the wall
    if (data->side == 0)
    {
        wall_hit_x = data->p_pos.x + ray_dist * data->ray_dir.x;
        map_x = (int)wall_hit_x;
        wall_hit_y = data->p_pos.y + ray_dist * data->ray_dir.y;
        tex_coordinates[0] = (int)((wall_hit_y - floor(wall_hit_y)) * data->textures->text_width);
    }
    else
    {
        wall_hit_x = data->p_pos.x + ray_dist * data->ray_dir.x;
        wall_hit_y = data->p_pos.y + ray_dist * data->ray_dir.y;
        map_y = (int)wall_hit_y;
        tex_coordinates[0] = (int)((wall_hit_x - floor(wall_hit_x)) * data->textures->text_width);
    }

    // Flip texture if needed
    if ((data->side == 0 && data->ray_dir.x < 0) ||
        (data->side == 1 && data->ray_dir.y > 0))
        tex_coordinates[0] = data->textures->text_width - tex_coordinates[0] - 1;

    // Ensure texture coordinate is within bounds
    tex_coordinates[0] &= (data->textures->text_width - 1);
}

static void	get_y_coordinates(int *tex_coordinates, t_data *data, int wall_height, int y)
{
	double	tex_pos;
	int		tex_y;
	double	wall_pos;

	// Calculate distance from top of wall to current pixel
	wall_pos = y - (HEIGHT / 2) + (wall_height / 2);
	// Calculate texture y coordinate
	tex_pos = (wall_pos * data->textures->text_height) / wall_height;
	tex_y = (int)tex_pos & (data->textures->text_height - 1);

	tex_coordinates[1] = tex_y;
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
	wall_data.draw_bounds[1] = (HEIGHT + wall_data.height) / 2;
	if (wall_data.draw_bounds[1] >= HEIGHT)
		wall_data.draw_bounds[1] = HEIGHT - 1;
	get_x_coordinates(wall_data.tex_coordinates, data, ray_dist);
	get_y_coordinates(wall_data.tex_coordinates, data, wall_data.height, y);
	color = ((uint32_t*)data->textures->text_addr[dir])[wall_data.tex_coordinates[1] * data->textures->text_width + wall_data.tex_coordinates[0]];
	rc_mlx_pixel_put(&data->image, x, y, color);
}
