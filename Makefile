# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okoca <okoca@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 11:20:19 by okoca             #+#    #+#              #
#    Updated: 2024/08/15 00:49:16 by tsuchen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d 

SRCS_M		= main.c

SRCS_REPO1	= 

SRCS_REPO2	= 

SRC 		= srcs/

REPO1_PATH	= srcs/repo1/
REPO2_PATH	= srcs/repo2/

SRCS		= $(addprefix $(SRC), $(SRCS_M)) \
		  $(addprefix $(REPO1_PATH), $(SRCS_REPO1)) \
		  $(addprefix $(REPO2_PATH), $(SRCS_REPO2)) \

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
