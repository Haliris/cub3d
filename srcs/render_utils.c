/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:12:17 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/30 14:37:39 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rc_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
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
			rc_mlx_pixel_put(&data->image, x, y, data->textures->ceiling);
		else if (y > (HEIGHT + wall_height) / 2)
			rc_mlx_pixel_put(&data->image, x, y, data->textures->floor);
		else
			mlx_render_wall(data, x, y, ray_dist);
	}
}
