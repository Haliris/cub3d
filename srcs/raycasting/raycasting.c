/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:13:34 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/28 18:17:43by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	rc_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void	rc_stripe_pixel_put(t_image *image, int x, double ray_dist)
{
	int	y;
	int	wall_height;

	wall_height = (int)(HEIGHT / ray_dist);
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

void	rc_ray_init(t_vec *dist_ray, t_vec *ray_pos, t_vec *ray_dir, t_vec *unit_dst)
{
	if (ray_dir->x < 0)
		dist_ray->x = (ray_pos->x - (int)ray_pos->x) * unit_dst->x;
	else
		dist_ray->x = ((int)ray_pos->x + 1.0 - ray_pos->x) * unit_dst->x;
	if (ray_dir->y < 0)
		dist_ray->y = (ray_pos->y - (int)ray_pos->y) * unit_dst->y;
	else
		dist_ray->y = ((int)ray_pos->y + 1.0 - ray_pos->y) * unit_dst->y;
}

int	rc_dda(t_vec *dist_ray, t_vec *unit_dist, t_vec *ray_pos, t_vec *ray_dir)
{
	if (dist_ray->x < dist_ray->y)
	{
		dist_ray->x += unit_dist->x;
		if (ray_dir->x < 0)
			ray_pos->x -= 1;
		else
			ray_pos->x += 1;
		return (0);
	}
	else
	{
		dist_ray->y += unit_dist->y;
		if (ray_dir->y < 0)
			ray_pos->y -= 1;
		else
			ray_pos->y += 1;
		return (1);
	}
}

double	rc_raydist(t_vec *ray, t_data *data)
{
	t_vec	ray_pos;
	t_vec	unit_dist;
	t_vec	dist_ray;
	int		side;

	vec_init(&ray_pos, (int)data->p_pos.x, (int)data->p_pos.y);
	unit_dist.x = sqrt(1 + ((ray->y * ray->y) / (ray->x * ray->x)));
	unit_dist.y = sqrt(1 + ((ray->x * ray->x) / (ray->y * ray->y)));
	rc_ray_init(&dist_ray, &ray_pos, ray, &unit_dist);
	while (1)
	{
		side = rc_dda(&dist_ray, &unit_dist, &ray_pos, ray);
		if (data->map[ray_pos.x][ray_pos.y] == '1')
			break ;
	}
	if (side == 1)
		return ((dist_ray_y - unit_dist_y) * vec_cos(ray, data->p_dir));
	else
		return ((dist_ray_x - unit_dist_x) * vec_cos(ray, data->p_dir));
}

void	rc_rendering(t_data *data)
{
	int		x;
	double	cam_x;
	double	ray_dist;
	t_vec	ray_dir;

	mlx_clear_window(data->mlx, data->window);
	x = -1;
	while (++x < WIDTH)
	{
		cam_x = 2 * x / (double)WIDTH - 1;
		ray_dir.x = data->p_dir.x + data->p_cam.x * cam_x;
		ray_dir.y = data->p_dir.y + data->p_cam.y * cam_x;
		ray_dist = rc_raydist(&ray_dir, data);
		rc_stripe_pixel_put(data->image, x, ray_dist);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
}
