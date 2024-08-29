/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:41:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/29 16:42:46 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vec_cos(t_vec *vec_a, t_vec *vec_b)
{
	double	output;

	output = vec_dot(vec_a, vec_b) / (vec_absv(vec_a) * vec_absv(vec_b));
	return (output);
}

void	vec_copy_scale(t_vec *vec_a, const t_vec *vec_b, double scale)
{
	vec_a->x = vec_b->x;
	vec_a->y = vec_b->y;
	vec_muls(vec_a, scale);
}
