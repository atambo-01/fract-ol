# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atambo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 18:48:12 by atambo            #+#    #+#              #
#    Updated: 2025/03/26 21:07:07 by atambo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES		=	src/main.c\
				src/check_input.c\
				src/color.c\
				src/complex.c\
				src/draw_fractal.c\
				src/ft_atoi_f.c\
				src/inits.c\
				src/inputs.c\
				src/inputs_utils.c\
				src/utils.c\
				src/sierpinski.c\
				src/sierpinski_utils.c\


NAME		=	fractol
CC			=	cc
CFLAGS		=	-g #-Wall -Wextra -Werror
OBJS		=	$(SOURCES:.c=.o)
INCLUDES	=	-Iincludes

SUBDIR		=	./minilibx-linux ./ft_printf
LIBS		=	./ft_printf/ft_printf.a -Lminilibx-linux -l:libmlx_Linux.a\
				-L/usr/lib -lXext -lX11 -lm -lz

all: submake $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)

submake:
	$(foreach dir, $(SUBDIR), $(MAKE) -C $(dir);)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES)  -c $< -o $@

clean:
	rm -f $(OBJS)
	$(foreach dir, $(SUBDIR), $(MAKE) -C $(dir) clean;)

fclean: clean
	rm -f $(NAME)
	$(foreach dir, $(SUBDIR), $(MAKE) -C $(dir) fclean;)

re: fclean all

# Phony targets
.PHONY: all clean fclean re submake

