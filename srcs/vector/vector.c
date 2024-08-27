/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:11:34 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/27 13:32:54 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vec_init(t_vec *vec, double x, double y)
{
	vec->x = x;
	vec->y = y;
}

void	vec_add(t_vec *vec_a, const t_vec *vec_b)
{
	vec_a->x = vec_a->x + vec_b->x;
	vec_a->y = vec_a->y + vec_b->y;
}

void	vec_sub(t_vec *vec_a, const t_vec *vec_b)
{
	vec_a->x = vec_a->x - vec_b->x;
	vec_a->y = vec_b->y - vec_b->y;
}

void	vec_muls(t_vec *vec, double scalar)
{
	vec->x = vec->x * scalar;
	vec->y = vec->y * scalar;
}

double	vec_dot(const t_vec *vec_a, const t_vec *vec_b)
{
	double	dot;

	dot = (vec_a->x * vec_b->x) + (vec_a->y * vec_b->y);
	return (dot);
}
