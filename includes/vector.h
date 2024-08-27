/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:56:32 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/27 11:41:19 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

void	vec_init(t_vec *vec, double x, double y);
void	vec_rotate(t_vec *vec, double angle);
t_vec	vec_dot(t_vec *vec_a, t_vec *vec_b);

#endif
