/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:00:57 by jteissie          #+#    #+#             */
/*   Updated: 2024/09/04 13:29:24 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3d.h"
# define TEXTURES_NB 7
# define TEXTURES_PATHS 5

typedef enum e_bool		t_bool;
typedef struct s_data	t_data;
typedef enum e_texture
{
	N = 0,
	S = 1,
	E = 2,
	W = 3,
	D = 4,
}	t_texture;

typedef struct s_textdata
{
	void		*text_img[TEXTURES_PATHS];
	int			tex_h[TEXTURES_PATHS];
	int			tex_w[TEXTURES_PATHS];
	char		*text_paths[TEXTURES_PATHS];
	char		*text_addr[TEXTURES_PATHS];
	int			floor;
	int			ceiling;
	int			textures_nb;
}	t_textdata;

typedef enum e_parse_status
{
	MAP_OK,
	MAP_ERR,
	PANIC_ERR,
}	t_parse_status;

int				parse_map(t_data *data);
char			**build_map(t_data *data, char *line);
void			panic_free(char **array);
t_bool			is_invalid_char(char c);
t_parse_status	check_invalid_chars(char **map);
void			fill_whitespaces(char **map);
t_textdata		*get_textures_info(t_data *data, char **line);
t_parse_status	find_start(uint32_t coordinate[], char **map);
int				ft_atoi_texture(t_textdata *textures, int *color, char *line);
int				add_info_buff(char *line, t_textdata *textures, t_texture type);
int				check_textpaths(char **paths);
void			panic_clean(t_textdata *textures);

#endif
