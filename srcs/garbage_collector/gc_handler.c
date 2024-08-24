/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:23:22 by marvin            #+#    #+#             */
/*   Updated: 2024/08/24 17:23:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

int	gc_init(t_gc_container *gc, pthread_t *gc_thread)
{
	memset(gc->garbage, 0, MAX_GARBAGE * sizeof(void *));
	memset(gc->garbage_type, 0, MAX_GARBAGE * sizeof(t_type));
	memset(gc->garbage_size, 0, MAX_GARBAGE * sizeof(size_t));
	gc->last_pos = 0;
	gc->run_status = RUN;
	if (pthread_mutex_init(&gc->garbage_lock, NULL) != 0)
		return (1);
	if (pthread_create(gc_thread, NULL, gc_routine, gc) != 0)
	{
		pthread_mutex_destroy(&gc->garbage_lock);
		return (1);
	}
	return (0);
}

void	gc_destroy(t_gc_container *gc, pthread_t *gc_thread)
{
	pthread_mutex_lock(&gc->garbage_lock);
	gc->run_status = STOP;
	pthread_mutex_unlock(&gc->garbage_lock);
	pthread_join(*gc_thread, NULL);
	gc_thread = NULL;
	pthread_mutex_destroy(&gc->garbage_lock);
	memset(gc->garbage, 0, MAX_GARBAGE * sizeof(void *));
	memset(gc->garbage_type, 0, MAX_GARBAGE * sizeof(t_type));
	memset(gc->garbage_size, 0, MAX_GARBAGE * sizeof(size_t));
}
