/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:40:50 by jteissie          #+#    #+#             */
/*   Updated: 2024/08/27 18:45:30 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_data *data, int value)
{

}

static void	move_camera(t_data *data, int value)
{

}

void	key_events(int keycode, t_data *data)
{
	int	value;

	value = 0;
	if (keycode == ARROW_RIGHT)
		move_player(data, value);
	else if (keycode == ARROW_LEFT)
		move_player(data, value);
	else if (keycode == ARROW_UP)
		move_player(data, value);
	else if (keycode == ARROW_DOWN)
		move_player(data, value);
	else if (keycode == W_KEY)
		move_camera(data, value);
	else if (keycode == S_KEY)
		move_camera(data, value);
	else if (keycode == A_KEY)
		move_camera(data, value);
	else if (keycode == D_KEY)
		move_camera(data, value);
	else if (keycode == ESC_KEY)
	{
		cleanup(data);
		exit(EXIT_SUCCESS);
	}
}
