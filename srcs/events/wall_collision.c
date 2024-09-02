/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:52:46 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/02 11:18:17 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_check(t_vec *step, t_data *data, int add_or_sub)
{
	t_vec	p_pos_tmp;

	p_pos_tmp = data->p_pos;
	if (add_or_sub == 1)
		vec_sub(&p_pos_tmp, step);
	else
		vec_add(&p_pos_tmp, step);
	if (data->map[(int)p_pos_tmp.x][(int)p_pos_tmp.y] == '1')
		return ;
	if (add_or_sub == 1)
		vec_sub(&data->p_pos, step);
	else
		vec_add(&data->p_pos, step);
}
