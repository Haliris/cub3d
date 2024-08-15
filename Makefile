# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/15 12:02:08 by tsuchen           #+#    #+#              #
#    Updated: 2024/08/15 14:18:08 by jteissie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d

SRCS_M		= main.c

SRCS_PS		= parser.c

SRCS_MAP	= map.c

SRCS_RC		= raycasting.c

PATH_M		= srcs/
PATH_PS		= srcs/parser/
PATH_MAP	= srcs/map/
PATH_RC		= srcs/raycasting/

SRCS		= $(addprefix $(PATH_M), $(SRCS_M)) \
		  $(addprefix $(PATH_PS), $(SRCS_PS)) \
		  $(addprefix $(PATH_MAP), $(SRCS_MAP)) \
		  $(addprefix $(PATH_RC), $(SRCS_RC))

HEADERS		= cub3d.h

OBJS		= $(SRCS:.c=.o)

HEAD		= includes/

CFLAGS		= -Wall -Wextra -Werror # -g

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
	git clone git@github.com:42Paris/minilibx-linux.git $@

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

.PHONY:	all clean fclean re bonus libft libft-clean libft-fclean root-clean root-fclean
