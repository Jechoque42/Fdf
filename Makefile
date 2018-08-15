# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jechoque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/14 10:30:54 by jechoque          #+#    #+#              #
#    Updated: 2017/11/29 14:04:04 by jechoque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=	fdf
FLAG=	-Wall -Wextra -Werror
SRC=	src/main.c \
	src/fdf_parser.c \
	src/fdf_draw.c \
	src/fdf_error.c \
	src/fdf_keycode.c \

OBJ=	src/main.o \
	src/fdf_parser.o \
	src/fdf_draw.o \
	src/fdf_error.o \
	src/fdf_keycode.o \

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc $(FLAG) -o $(NAME) -I ./include/ $(SRC) libft/libft.a -lmlx -framework OpenGL -framework Appkit

clean:
	rm -rf $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
