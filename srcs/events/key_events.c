/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:40:50 by jteissie          #+#    #+#             */
/*   Updated: 2024/09/02 17:24:13 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_data *data, t_move dir)
{
	t_vec	step;

	if (dir == FORWARD)
	{
		vec_copy_scale(&step, &data->p_dir, MOV_STEP);
		move_check(&step, data, 0);
	}
	else if (dir == BACKWARD)
	{
		vec_copy_scale(&step, &data->p_dir, MOV_STEP);
		move_check(&step, data, 1);
	}
	else if (dir == RIGHT)
	{
		vec_copy_scale(&step, &data->p_cam, MOV_STEP);
		move_check(&step, data, 0);
	}
	else if (dir == LEFT)
	{
		vec_copy_scale(&step, &data->p_cam, MOV_STEP);
		move_check(&step, data, 1);
	}
	return ;
}

static void	key_move_camera(t_data *data, t_rot dir)
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

static void	pause_game(t_data *data)
{
	if (data->pause == TRUE)
	{
		mlx_mouse_hide(data->mlx, data->window);
		data->pause = FALSE;
	}
	else
	{
		mlx_mouse_show(data->mlx, data->window);
		data->pause = TRUE;
	}
}

int	key_events(int keycode, t_data *data)
{
	if (keycode == P_KEY)
		pause_game(data);
	else if (keycode == ARROW_RIGHT && data->pause == FALSE)
		key_move_camera(data, CLOCK);
	else if (keycode == ARROW_LEFT && data->pause == FALSE)
		key_move_camera(data, CCLOCK);
	else if (keycode == W_KEY && data->pause == FALSE)
		move_player(data, FORWARD);
	else if (keycode == S_KEY && data->pause == FALSE)
		move_player(data, BACKWARD);
	else if (keycode == A_KEY && data->pause == FALSE)
		move_player(data, LEFT);
	else if (keycode == D_KEY && data->pause == FALSE)
		move_player(data, RIGHT);
	else if (keycode == ESC_KEY)
		cleanup(data);
	return (SUCCESS);
}
