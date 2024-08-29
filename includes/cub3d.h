/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 00:19:44 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/29 11:16:16 by tsuchen          ###   ########.fr       */
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
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"

# include "parser.h"
# include "vector.h"
# include "raycasting.h"

# define SUCCESS 0
# define PANIC 1

# define OUT STDOUT_FILENO
# define IN STDIN_FILENO
# define ER STDERR_FILENO
# define P_NAME "cub3d"

# define WIDTH 1280
# define HEIGHT 720
# define FOV 90
# define KEY_PRESS 2
# define MOUSE_PRESS 4
# define MOUSE_MOVE 6
# define CLOSE_BUTTON 17
# define FILE_EXTENSION ".cub"

typedef enum e_texture		t_texture;
typedef struct s_textdata	t_textdata;

typedef enum e_keys
{
	ARROW_RIGHT = 65363,
	ARROW_LEFT = 65361,
	ARROW_UP = 65362,
	ARROW_DOWN = 65364,
	ESC_KEY = 65307,
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
}	t_keys;
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
	char		*map_path;
	int			map_fd;
	size_t		map_bound;
	size_t		map_start;
	char		**map;
	void		*mlx;
	void		*window;
	t_image		*image;
	t_textdata	*textures;
	t_p_dir		p_dir_default;
	t_vec		p_pos;
	t_vec		p_dir;
	t_vec		p_cam;
	t_p_dir		spawn_dir;
}	t_data;

int		cleanup(t_data *data);
int		game_init(t_data *data);
int		key_events(int keycode, t_data *data);
/* color utils*/
int		create_trgb(int t, int r, int g, int b);
int		get_color(int trgb, char index);
int		add_shade(double factor, int color);
int		get_opposite(int color);

#endif
