/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:39:13 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/27 18:37:26 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define WIDTH 1280
# define HEIGHT 720

typedef struct s_vec	t_vec;
typedef struct s_data	t_data;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

void	rc_mlx_pixel_put(t_image *image, int x, int y, int color);
void	rc_strip_pixel_put(t_image *image, int x, double ray_dist);
double	rc_raydist(t_vec *ray, t_data *data);

#endif