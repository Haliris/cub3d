/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 00:19:44 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/16 19:18:23 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <math.h>

# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"

# include "parser.h"

# define SUCCESS 0
# define PANIC 1

# define OUT STDOUT_FILENO
# define IN STDIN_FILENO
# define ER STDERR_FILENO
# define P_NAME "cub3d"

# define KEY_PRESS 2
# define MOUSE_PRESS 4
# define MOUSE_MOVE 6
# define CLOSE_BUTTON 17
# define FILE_EXTENSION ".cub"

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef enum e_p_dir
{
	NORTH = 'N',
	SOUTH = 'S',
	WEST = 'W',
	EAST = 'E',
}	t_p_dir;
typedef struct s_data
{
	char	*map_path;
	int		map_fd;
	size_t	map_bound;
	char	**map;
	t_p_dir	p_dir;
}	t_data;

#endif
