/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:12:17 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/29 15:49:14 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	rc_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
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
}

void	mlx_render_wall(t_data *data, int x, int y, double ray_dist)
{
	int	wall_height;
	int	draw_bounds[2];
	int	tex_coordinates[2];

	wall_height = (int)(HEIGHT / ray_dist);
	draw_bounds[0] = (HEIGHT - wall_height) / 2;
	if (draw_bounds[0] < 0)
		draw_bounds[0] = 0;
	draw_bounds[1] = (HEIGHT + wall_height) / 2;
	if (draw_bounds[1] >= HEIGHT)
		draw_bounds[1] = HEIGHT - 1;
	get_tex_coordinates(tex_coordinates, data, wall_height, ray_dist)
}

void	rc_stripe_pixel_put(t_data *data, int x, double ray_dist)
{
	int	y;
	int	wall_height;

	wall_height = (int)(HEIGHT / ray_dist);
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < (HEIGHT - wall_height) / 2)
			rc_mlx_pixel_put(data->image, x, y, data->textures->ceiling);
		else if (y > (HEIGHT + wall_height) / 2)
			rc_mlx_pixel_put(data->image, x, y, data->textures->floor);
		else
			mlx_render_wall(data, x, y, ray_dist);
	}
}
