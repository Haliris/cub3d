/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:40:50 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/29 16:52:06 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_data *data, t_move dir)
{
	t_vec	step;

	if (dir == FORWARD)
	{
		vec_copy_scale(&step, &data->p_dir, MOV_STEP);
		vec_add(&data->p_pos, &step);
	}
	else if (dir == BACKWARD)
	{
		vec_copy_scale(&step, &data->p_dir, MOV_STEP);
		vec_sub(&data->p_pos, &step);
	}
	else if (dir == RIGHT)
	{
		vec_copy_scale(&step, &data->p_cam, MOV_STEP);
		vec_add(&data->p_pos, &step);
	}
	else if (dir == LEFT)
	{
		vec_copy_scale(&step, &data->p_cam, MOV_STEP);
		vec_sub(&data->p_pos, &step);
	}
	return ;
}

static void	move_camera(t_data *data, t_rot dir)
{
	if (dir == CLOCK)
	{
		vec_rotate(&data->p_cam, ROT_STEP * -1);
		vec_rotate(&data->p_dir, ROT_STEP * -1);
	}
	else
	{
		vec_rotate(&data->p_cam, ROT_STEP);
		vec_rotate(&data->p_dir, ROT_STEP);
	}
	return ;
}

int	key_events(int keycode, t_data *data)
{
	if (keycode == ARROW_RIGHT)
		move_camera(data, CLOCK);
	else if (keycode == ARROW_LEFT)
		move_camera(data, CCLOCK);
	else if (keycode == W_KEY)
		move_player(data, FORWARD);
	else if (keycode == S_KEY)
		move_player(data, BACKWARD);
	else if (keycode == A_KEY)
		move_player(data, LEFT);
	else if (keycode == D_KEY)
		move_player(data, RIGHT);
	else if (keycode == ESC_KEY)
		cleanup(data);
	return (SUCCESS);
}
