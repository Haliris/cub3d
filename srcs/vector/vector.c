/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:11:34 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/27 15:46:44 by tsuchen          ###   ########.fr       */
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
	vec_a->y = vec_a->y - vec_b->y;
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

// int	main(void)
// {
// 	t_vec	a;
// 	t_vec	b;

// 	vec_init(&a, 3, 4);
// 	vec_init(&b, 1, 2);
// 	printf("vec_a init ax: %.2f, ay: %.2f\n", a.x, a.y);
// 	printf("vec_b init bx: %.2f, by: %.2f\n", b.x, b.y);
// 	vec_add(&a, &b);
// 	printf("vec_a after adding b ax: %.2f, ay: %.2f\n", a.x, a.y);
// 	vec_sub(&a, &b);
// 	printf("vec_a after minus b ax: %.2f, ay: %.2f\n", a.x, a.y);
// 	vec_muls(&a, 5);
// 	printf("vec_a after multiply by 5 ax: %.2f, ay: %.2f\n", a.x, a.y);
// 	printf("vec_a dot vec_b is %.2f\n", vec_dot(&a, &b));
// 	printf("abs of a is %.2f\n", vec_absv(&a));
// 	printf("dist between a and b: %.2f\n", vec_dist(&a, &b));
// 	vec_mirror(&a);
// 	printf("vec_a after mirror ax: %.2f, ay: %.2f\n", a.x, a.y);
// 	vec_transp(&a);
// 	printf("vec_a after transp ax: %.2f, ay: %.2f\n", a.x, a.y);
// 	vec_rotate(&b, 30);
// 	printf("vec_b after rotate 30 degree bx: %.2f, by: %.2f\n", b.x, b.y);
// 	return (0);
// }
