/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:59:13 by jteissie          #+#    #+#             */
/*   Updated: 2024/09/04 12:25:22 by tsuchen          ###   ########.fr       */
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
		else if (data->map[(int)ray_pos.x][(int)ray_pos.y] == 'D'
		|| data->map[(int)ray_pos.x][(int)ray_pos.y] == 'O')
			break ;
	}
	if (data->side == 1)
		return ((dist_ray.y - unit_dist.y) * vec_cos(ray, &data->p_dir));
	else
		return ((dist_ray.x - unit_dist.x) * vec_cos(ray, &data->p_dir));
}

static void	change_door_state(t_data *data, t_vec *p_ray)
{
	int		door_x;
	int		door_y;

	door_x = data->p_pos.x + p_ray->x;
	door_y = data->p_pos.y + p_ray->y;
	if (data->map[door_x][door_y] == 'D')
		play_sprite_forward(data, door_x, door_y);
	else if (data->map[door_x][door_y] == 'O')
		play_sprite_backward(data, door_x, door_y);
}

void	interact_door(t_data *data)
{
	t_vec	p_ray;
	double	dist;

	p_ray.x = data->p_dir.x;
	p_ray.y = data->p_dir.y;
	dist = get_door_dist(&p_ray, data);
	if (dist > 0.5)
		return ;
	change_door_state(data, &p_ray);
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

int	mouse_move(int x, int y, t_data *data)
{
	if (data->pause == TRUE)
		return (0);
	if (x == WIDTH / 2 && y == HEIGHT / 2)
		return (SUCCESS);
	if (x >= WIDTH / 2)
	{
		vec_rotate(&data->p_cam, MOUSE_ROT_STEP * -1);
		vec_rotate(&data->p_dir, MOUSE_ROT_STEP * -1);
	}
	else
	{
		vec_rotate(&data->p_cam, MOUSE_ROT_STEP);
		vec_rotate(&data->p_dir, MOUSE_ROT_STEP);
	}
	mlx_mouse_move(data->mlx, data->window, WIDTH / 2, HEIGHT / 2);
	return (SUCCESS);
}
