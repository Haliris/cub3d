/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:12:17 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/29 15:44:21 by tsuchen          ###   ########.fr       */
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
			rc_mlx_pixel_put(&data->image, x, y, get_opposite(data->textures->ceiling));
	}
}
