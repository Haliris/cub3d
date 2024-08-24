/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:29:45 by marvin            #+#    #+#             */
/*   Updated: 2024/08/24 13:29:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

static int	wait_for_free_slot(t_gc_container *container)
{
	size_t	cycles;

	cycles = 0;
	while (cycles < 15)
	{
		usleep(1 * SECOND);
		pthread_mutex_lock(&container->garbage_lock);
		if (container->last_pos != MAX_GARBAGE - 1)
		{
			pthread_mutex_unlock(&container->garbage_lock);
			return (0);
		}
		else
		{
			cycles++;
			pthread_mutex_unlock(&container->garbage_lock);
		}
	}
	write(STDERR_FILENO, "Error: GC: Wait for free slot timeout\n", 39);
	return (1);
}

int	add_del(void *ptr, t_type type, size_t size, t_gc_container *container)
{
	size_t	insert_pos;

	pthread_mutex_lock(&container->garbage_lock);
	insert_pos = container->last_pos;
	if (insert_pos == MAX_GARBAGE - 1)
	{
		pthread_mutex_unlock(&container->garbage_lock);
		if (wait_for_free_slot(container) == 0)
			return (1);
		pthread_mutex_lock(&container->garbage_lock);
		insert_pos = container->last_pos;
	}
	container->garbage[insert_pos] = ptr;
	container->garbage_type[insert_pos] = type;
	container->garbage_size[insert_pos] = size;
	container->last_pos++;
	pthread_mutex_unlock(&container->garbage_lock);
	return (0);
}
