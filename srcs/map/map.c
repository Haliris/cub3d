/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:13:17 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/02 16:11:42 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_mini_map(t_data *data)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	x = 0;
	while (x < MINI_MAP_W)
	{
		y = 0;
		while (y < MINI_MAP_H)
		{
			map_x = x * (data->map_width - 1) / MINI_MAP_W;
			map_y = y * (data->map_bound) / MINI_MAP_H;
			if (data->map[map_y][map_x] == '1')
				rc_mlx_pixel_put(&data->mini_map, x, y, 0xFF0000);
			else
				rc_mlx_pixel_put(&data->mini_map, x, y, 0x00FF00);
			if (map_y == (int)data->p_pos.x && map_x == (int)data->p_pos.y)
			{
				rc_mlx_pixel_put(&data->mini_map, x, y, 0x0000FF);
			}
			y++;
		}
		x++;
	}
}
