/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:59:13 by jteissie          #+#    #+#             */
/*   Updated: 2024/09/02 13:33:50 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
