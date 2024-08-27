/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:13:34 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/27 18:40:43 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	rc_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void	rc_strip_pixel_put(t_image *image, int x, double ray_dist)
{
	int	y;
	int	wall_height;

	wall_height = ; // something reverse related to ray_dist
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < (HEIGHT - wall_height) / 2)
			rc_mlx_pixel_put(image, x, y, color_cieling);
		else if (y > (HEIGHT + wall_height) / 2)
			rc_mlx_pixel_put(image, x, y, color_floor);
		else
			rc_mlx_pixel_put(image, x, y, color_wall);
	}
}

double	rc_raydist(t_vec *ray, t_data *data)
{
	double	dist;

	dist = 0.0f;
	
	/* take an individual ray vector and calculate distance from P to Wall*/
}

