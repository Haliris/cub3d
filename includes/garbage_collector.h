/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:29:50 by marvin            #+#    #+#             */
/*   Updated: 2024/08/24 17:25:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# define MAX_GARBAGE 100
# define STOP 0
# define RUN 1
# define SECOND 1000000

typedef enum e_type
{
	NULL_TYPE,
	POINTER,
	ARRAY,
	IMAGE,
	WINDOW,
	MLX,
}	t_type;

typedef struct s_gc_container
{
	void			*garbage[MAX_GARBAGE];
	t_type			garbage_type[MAX_GARBAGE];
	size_t			garbage_size[MAX_GARBAGE];
	size_t			last_pos;
	int				run_status;
	pthread_mutex_t	garbage_lock;
}	t_gc_container;

int		gc_init(t_gc_container *gc, pthread_t *gc_thread);
void	gc_destroy(t_gc_container *gc, pthread_t *gc_thread);
int		add_del(void *ptr, t_type type, size_t size, t_gc_container *container);
void	*gc_routine(void *arg);
#endif 
