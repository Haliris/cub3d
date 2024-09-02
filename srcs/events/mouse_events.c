/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:59:13 by jteissie          #+#    #+#             */
/*   Updated: 2024/09/02 12:16:18 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	mouse_move_camera()


int	mousemove_events(int x, int y, t_data *data)
{
	(void)data;
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	mlx_mouse_move(data->mlx, data->window, WIDTH / 2, HEIGHT / 2);
	return (SUCCESS);
}
