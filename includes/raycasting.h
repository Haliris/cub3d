/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:39:13 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/29 15:33:45 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "vector.h"
# include "cub3d.h"

typedef struct s_data	t_data;

int		rc_dda(t_vec *dist, t_vec *unit_dist, t_vec *pos, t_vec *dir);
void	rc_ray_init(t_vec *dist, t_vec *pos, t_vec *dir, t_vec *unit_dst);
double	rc_raydist(t_vec *ray, t_data *data);
int		rc_rendering(t_data *data);

#endif