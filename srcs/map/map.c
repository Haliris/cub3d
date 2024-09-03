/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:13:17 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/03 19:22:23 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_mini_map(t_data *data)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	y = -1;
	while (++y < MINI_MAP_H)
	{
		x = -1;
		while (++x < MINI_MAP_W)
		{
			map_y = y * (data->map_bound) / MINI_MAP_H;
			map_x = x * (data->map_width - 1) / MINI_MAP_W;
			if ((map_x < (int)(ft_strlen(data->map[map_y]) - 1))
				&& data->map[map_y][map_x] == '1')
				rc_mlx_pixel_put(&data->mini_map, x, y, 0x212529);
			else if ((map_x < (int)(ft_strlen(data->map[map_y]) - 1))
				&& data->map[map_y][map_x] == 'D')
				rc_mlx_pixel_put(&data->mini_map, x, y, 0xFFC300);
			else
				rc_mlx_pixel_put(&data->mini_map, x, y, 0xE9ECEF);
			if ((int)data->p_pos.x == map_y && (int)data->p_pos.y == map_x)
				rc_mlx_pixel_put(&data->mini_map, x, y, 0xD62828);
		}
	}
}
