# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atambo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 20:48:45 by atambo            #+#    #+#              #
#    Updated: 2024/09/30 20:48:49 by atambo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =	./src/check_input.c \
		./src/color.c \
		./src/complex.c \
		./src/draw_fractal.c \
		./src/ft_atoi_f.c \
		./src/inits.c \
		./src/inputs.c \
		./src/inputs_utils.c \
		./src/main.c \
		./src/utils.c
      
      

OBJS = $(SRCS:.c=.o)
INCLUDES = -Iincludes

SUBDIR = ./minilibx-linux 

all: submake $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) \
	-Lminilibx-linux -l:libmlx_Linux.a -L/usr/lib -lXext -lX11 -lm -lz

submake:
	$(MAKE) -C $(SUBDIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -Iminilibx-linux -O1 -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Phony targets

.PHONY: all clean fclean re submake

