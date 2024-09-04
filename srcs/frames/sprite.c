/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:59:13 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/04 11:47:39 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_sprite_forward(t_data *data, int map_x, int map_y)
{
	t_frame	*beg_frame;
	void	*door_img;
	char	*door_addr;
	int		door_h;
	int		door_w;
	int		c;

	printf("in play sprite\n");
	beg_frame = data->frames;
	door_img = data->textures->text_img[D];
	door_addr = data->textures->text_addr[D];
	door_h = data->textures->tex_h[D];
	door_w = data->textures->tex_w[D];
	while (beg_frame)
	{
		data->textures->text_img[D] = beg_frame->img;
		data->textures->text_addr[D] = beg_frame->addr;
		data->textures->tex_h[D] = beg_frame->frm_h;
		data->textures->tex_w[D] = beg_frame->frm_w;
		c = 0;
		while (c++ < 10000)
			rc_rendering(data);
		beg_frame = beg_frame->next;
	}
	data->map[map_x][map_y] = 'O';
	data->textures->text_img[D] = door_img;
	data->textures->text_addr[D] = door_addr;
	data->textures->tex_h[D] = door_h;
	data->textures->tex_w[D] = door_w;
}
