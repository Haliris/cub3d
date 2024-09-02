/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 00:19:44 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/02 15:07:28 by jteissie         ###   ########.fr       */
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

# define SUCCESS 0
# define PANIC 1

# define OUT STDOUT_FILENO
# define IN STDIN_FILENO
# define ER STDERR_FILENO
# define P_NAME "cub3d"

# define WIDTH 1280
# define HEIGHT 720
# define FOV 90
# define ROT_STEP 1.5f
# define MOV_STEP 0.1f
# define KEY_PRESS 2
# define MOUSE_PRESS 4
# define MOUSE_MOVE 6
# define FILE_EXTENSION ".cub"

typedef enum e_texture		t_texture;
typedef struct s_textdata	t_textdata;
typedef struct s_image		t_image;
typedef struct s_wall
{
	int	height;
	int	draw_bounds[2];
	int	tex_pos[2];
}	t_wall;
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
	M1 = 65307,
}	t_keys;
typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef enum e_rot
{
	CLOCK,
	CCLOCK,
}	t_rot;

typedef enum e_move
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
}	t_move;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_data
{
	char		*map_path;
	int			map_fd;
	size_t		map_bound;
	char		**map;
	void		*mlx;
	void		*window;
	t_image		image;
	t_textdata	*textures;
	t_wall		w_data;
	t_vec		p_pos;
	t_vec		p_dir;
	t_vec		p_cam;
	t_vec		ray_dir;
	int			side;
}	t_data;

int		cleanup(t_data *data);
int		game_init(t_data *data);
int		key_events(int keycode, t_data *data);
void	move_check(t_vec *step, t_data *data, int add_or_sub);
int		mouse_press(int button, int x, int y, t_data *data);
/* color utils*/
int		create_trgb(int t, int r, int g, int b);
int		get_color(int trgb, char index);
int		add_shade(double factor, int color);
int		get_opposite(int color);
/* RC Rendering */
int		rc_dda(t_vec *dist, t_vec *unit_dist, t_vec *pos, t_vec *dir);
void	rc_ray_init(t_vec *dist, t_vec *pos, t_vec *dir, t_vec *unit_dst);
double	rc_raydist(t_vec *ray, t_data *data);
int		rc_rendering(t_data *data);
void	rc_render_wall(t_data *data, int x, int y, double ray_dist);
void	rc_mlx_pixel_put(t_image *image, int x, int y, int color);
void	rc_stripe_pixel_put(t_data *data, int x, double ray_dist);

#endif
