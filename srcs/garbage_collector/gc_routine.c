/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:18:38 by marvin            #+#    #+#             */
/*   Updated: 2024/08/24 15:18:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

static void	free_array(void **ptr, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		free(ptr[index]);
		index++;
	}
	free(ptr);
}

static void	del(void *ptr, size_t size, t_type type)
{
	if (type == POINTER)
		free(ptr);
	else if (type == ARRAY)
		free_array((void **)ptr, size);
}

static void	sweep(t_gc_container *container)
{
	void	*ptr;
	size_t	size;
	size_t	position;
	t_type	type;

	position = container->last_pos;
	if (position == 0)
		return ;
	while (container->last_pos > 0)
	{
		position = container->last_pos - 1;
		ptr = container->garbage[position];
		size = container->garbage_size[position];
		type = container->garbage_type[position];
		del(ptr, size, type);
		container->garbage[position] = NULL;
		container->garbage_size[position] = 0;
		container->garbage_type[position] = NULL_TYPE;
		container->last_pos--;
	}
}

void	*gc_routine(void *arg)
{
	t_gc_container	*container;

	container = (t_gc_container *)arg;
	while (1)
	{
		pthread_mutex_lock(&container->garbage_lock);
		sweep(container);
		if (container->run_status == STOP)
		{
			pthread_mutex_unlock(&container->garbage_lock);
			break ;
		}
		pthread_mutex_unlock(&container->garbage_lock);
		usleep(5 * SECOND);
	}
	return (NULL);
}
