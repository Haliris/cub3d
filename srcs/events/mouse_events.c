/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:38 by jteissie          #+#    #+#             */
/*   Updated: 2024/09/02 15:50:21 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_door_dist(t_vec *ray, t_data *data)
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
			return (1);
		else if (data->map[(int)ray_pos.x][(int)ray_pos.y] == 'D')
			break ;
	}
	if (data->side == 1)
		return ((dist_ray.y - unit_dist.y) * vec_cos(ray, &data->p_dir));
	else
		return ((dist_ray.x - unit_dist.x) * vec_cos(ray, &data->p_dir));
}

static void	change_door_state(t_data *data, double dist)
{

}

static void	interact_door(t_data *data)
{
	t_vec	p_ray;
	double	dist;

	p_ray.x = data->p_dir.x;
	p_ray.y = data->p_dir.y;
	printf("p_ray.x: %f\n", p_ray.x);
	printf("p_ray.y: %f\n", p_ray.y);
	dist = get_door_dist(&p_ray, data);
	if (dist > 0.5)
	{
		printf("Door too far!\n");
		return ;
	}
	printf("In door range!\n");
	change_door_state(data, dist);
	return ;
}

int	mouse_press(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		interact_door(data);
	return (SUCCESS);
}
