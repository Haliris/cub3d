# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/15 12:02:08 by tsuchen           #+#    #+#              #
#    Updated: 2024/09/03 16:36:38 by tsuchen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d

SRCS_M		=	main.c \
				game_init.c \
				cleanup.c \
				color_utils.c


SRCS_PS		= 	parser.c \
				build_map.c \
				parser_utils.c \
				get_textures.c \
				get_textures_utils.c

SRCS_EV		=	key_events.c wall_collision.c mouse_events.c

SRCS_MAP	= map.c

SRCS_RC		= raycasting.c render_wall.c render_utils.c

SRCS_VEC	= vector.c vector_2.c vector_3.c

SRCS_FRM	= lst_add_back.c lst_clear.c lst_last.c lst_new.c lst_size.c

PATH_M		= srcs/
PATH_PS		= srcs/parser/
PATH_EV		= srcs/events/
PATH_MAP	= srcs/map/
PATH_RC		= srcs/raycasting/
PATH_VEC	= srcs/vector/
PATH_FRM	= srcs/frames/

SRCS		= $(addprefix $(PATH_M), $(SRCS_M)) \
		  $(addprefix $(PATH_PS), $(SRCS_PS)) \
		  $(addprefix $(PATH_EV), $(SRCS_EV)) \
		  $(addprefix $(PATH_MAP), $(SRCS_MAP)) \
		  $(addprefix $(PATH_RC), $(SRCS_RC)) \
		  $(addprefix $(PATH_VEC), $(SRCS_VEC)) \
		  $(addprefix $(PATH_FRM), $(SRCS_FRM))

HEADERS		= cub3d.h parser.h vector.h

OBJS		= $(SRCS:.c=.o)

HEAD		= includes/

CFLAGS		= -Wall -Wextra -Werror -g3

CC		= cc

H_DEPS		= $(addprefix $(HEAD), $(HEADERS))

LIBFT_PATH	= libft/
LIBFT_H_PATH	= libft/includes/
LIBFT		= -L $(LIBFT_PATH) -lft

MLX = minilibx-linux
MLXFLAGS	= -L $(MLX) -lmlx -lXext -lX11 -lXext -lm -lz -Ofast

all: minilibx-linux $(NAME)

$(NAME): $(OBJS) $(H_DEPS)
	make -C $(LIBFT_PATH) all
	make -C $(MLX) all
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIBFT) -o $(NAME)

minilibx-linux:
	@if [ ! -d "$@" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $@; \
	else \
		echo "mlx already present in the working directory, aborting clone."; \
	fi

bonus: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HEAD) -I$(LIBFT_H_PATH) -I$(MLX) -c $< -o $@

clean: libft-clean mlx-clean root-clean

libft-clean:
	$(MAKE) -C $(LIBFT_PATH) clean

mlx-clean:
	$(MAKE) -C $(MLX) clean

root-clean:
	rm -f $(OBJS)

fclean: libft-fclean root-fclean

libft-fclean:
	$(MAKE) -C $(LIBFT_PATH) fclean

root-fclean: root-clean
	rm -f $(NAME)
	rm -rf minilibx-linux

re: fclean all

.PHONY:	all clean fclean re bonus minilibx-linux mlx_clean libft-clean libft-fclean root-clean root-fclean
