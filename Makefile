# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/15 12:02:08 by tsuchen           #+#    #+#              #
#    Updated: 2024/08/15 12:14:25 by tsuchen          ###   ########.fr        #
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
LIBFT		= $(LIBFT_PATH)libft.a

MLX		= mlx_linux
MLXFLAGS	= -lmlx_Linux -lXext -lX11 -lm -lz

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS) $(H_DEPS)
	$(CC) $(CFLAGS) $(OBJS) -L$(MLX) -I$(MLX) $(MLXFLAGS) $(LIBFT) -o $(NAME)

bonus: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HEAD) -I$(LIBFT_H_PATH) -I$(MLX) -c $< -o $@

clean: libft-clean root-clean

libft-clean:
	$(MAKE) -C $(LIBFT_PATH) clean

root-clean:
	rm -f $(OBJS)

fclean: libft-fclean root-fclean

libft-fclean:
	$(MAKE) -C $(LIBFT_PATH) fclean

root-fclean: root-clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus libft libft-clean libft-fclean root-clean root-fclean
