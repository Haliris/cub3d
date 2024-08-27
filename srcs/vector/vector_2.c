/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:33:30 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/27 15:42:12 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vec_absv(const t_vec *vec)
{
	double	absv;

	absv = sqrt((vec->x * vec->x) + (vec->y * vec->y));
	return (absv);
}

double	vec_dist(const t_vec *vec_a, const t_vec *vec_b)
{
	double	dist;
	double	del_x;
	double	del_y;

	del_x = vec_b->x - vec_a->x;
	del_y = vec_b->y - vec_a->y;
	dist = sqrt((del_x * del_x) + (del_y * del_y));
	return (dist);
}

void	vec_mirror(t_vec *vec)
{
	vec->x = vec->x * -1;
	vec->y = vec->y * -1;
}

void	vec_transp(t_vec *vec)
{
	double	tmp;

	tmp = vec->x;
	vec->x = vec->y;
	vec->y = tmp;
}

void	vec_rotate(t_vec *vec, double angle)
{
	double	new_x;
	double	new_y;
	double	pi;
	double	angle_r;

	pi = acos(-1);
	angle_r = angle * pi / 180;
	new_x = vec->x * cos(angle_r) - vec->y * sin(angle_r);
	new_y = vec->x * sin(angle_r) + vec->y * cos(angle_r);
	vec->x = new_x;
	vec->y = new_y;
}
