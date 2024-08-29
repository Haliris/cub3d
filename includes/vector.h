/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:56:32 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/29 16:43:25 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>

# define PI 3.14159265359f

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

void	vec_init(t_vec *vec, double x, double y);
void	vec_add(t_vec *vec_a, const t_vec *vec_b);
void	vec_sub(t_vec *vec_a, const t_vec *vec_b);
void	vec_muls(t_vec *vec, double scalar);
double	vec_dot(const t_vec *vec_a, const t_vec *vec_b);
double	vec_absv(const t_vec *vec);
double	vec_dist(const t_vec *vec_a, const t_vec *vec_b);
void	vec_mirror(t_vec *vec);
void	vec_transp(t_vec *vec);
void	vec_rotate(t_vec *vec, double angle);
double	vec_cos(t_vec *vec_a, t_vec *vec_b);
void	vec_copy_scale(t_vec *vec_a, const t_vec *vec_b, double scale);

#endif
