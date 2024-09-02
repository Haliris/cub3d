/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:13:34 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/02 17:25:33 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rc_ray_init(t_vec *dist, t_vec *pos, t_vec *dir, t_vec *unit_dst)
{
	if (dir->x < 0)
		dist->x = (pos->x - (int)pos->x) * unit_dst->x;
	else
		dist->x = ((int)pos->x + 1.0 - pos->x) * unit_dst->x;
	if (dir->y < 0)
		dist->y = (pos->y - (int)pos->y) * unit_dst->y;
	else
		dist->y = ((int)pos->y + 1.0 - pos->y) * unit_dst->y;
}

int	rc_dda(t_vec *dist, t_vec *unit_dist, t_vec *pos, t_vec *dir)
{
	if (dist->x < dist->y)
	{
		dist->x += unit_dist->x;
		if (dir->x < 0)
			pos->x -= 1;
		else
			pos->x += 1;
		return (0);
	}
	else
	{
		dist->y += unit_dist->y;
		if (dir->y < 0)
			pos->y -= 1;
		else
			pos->y += 1;
		return (1);
	}
}

double	rc_raydist(t_vec *ray, t_data *data)
{
	t_vec	ray_pos;
	t_vec	unit_dist;
	t_vec	dist_ray;

	ray->door = FALSE;
	vec_init(&ray_pos, data->p_pos.x, data->p_pos.y);
	unit_dist.x = sqrt(1 + ((ray->y * ray->y) / (ray->x * ray->x)));
	unit_dist.y = sqrt(1 + ((ray->x * ray->x) / (ray->y * ray->y)));
	rc_ray_init(&dist_ray, &ray_pos, ray, &unit_dist);
	while (1)
	{
		data->side = rc_dda(&dist_ray, &unit_dist, &ray_pos, ray);
		if (data->map[(int)ray_pos.x][(int)ray_pos.y] == '1')
			break ;
		if (data->map[(int)ray_pos.x][(int)ray_pos.y] == 'D')
		{
			ray->door = TRUE;
			break ;
		}
	}
	if (data->side == 1)
		return ((dist_ray.y - unit_dist.y) * vec_cos(ray, &data->p_dir));
	else
		return ((dist_ray.x - unit_dist.x) * vec_cos(ray, &data->p_dir));
}

int	rc_rendering(t_data *data)
{
	int		x;
	double	cam_x;
	double	ray_dist;

	mlx_clear_window(data->mlx, data->window);
	x = -1;
	while (++x < WIDTH)
	{
		cam_x = 2 * x / (double)WIDTH - 1;
		data->ray_dir.x = data->p_dir.x + data->p_cam.x * cam_x;
		data->ray_dir.y = data->p_dir.y + data->p_cam.y * cam_x;
		ray_dist = rc_raydist(&data->ray_dir, data);
		rc_stripe_pixel_put(data, x, ray_dist);
	}
	put_mini_map(data);
	mlx_put_image_to_window(data->mlx, data->window, data->image.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->window, data->mini_map.img,
		MINI_MAP_X, MINI_MAP_Y);
	return (0);
}
