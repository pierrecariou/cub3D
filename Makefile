# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcariou <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/18 14:10:41 by pcariou           #+#    #+#              #
#    Updated: 2020/08/04 23:11:49 by pcariou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= Cub3D

HEADER		= ./

SRCS		= 	src/main.c \
				src/bmp.c \
				src/move.c \
				src/utils.c \
				src/main1.c \
				src/main2.c \
				src/main3.c \
				src/sprites.c \
				src/textcolo.c \
				parsing/parsexymap.c \
				parsing/parsexpm.c \
				parsing/parsecf.c \
				parsing/map.c \
				parsing/map1.c \
				parsing/parserepets.c \
				parsing/parsing.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS		= $(SRCS:.c=.o)

RM			= rm -f

AR			=  ar rcs

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

ATTRIBUT	= -c

all:		$(NAME)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(HEADER) -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext

$(NAME):	$(OBJS)
			cd libft && make
			$(CC) -o $(NAME) $(OBJS) libft/libft -lm -lmlx -lXext -lX11 -lbsd

clean:
			$(RM) $(OBJS) && cd libft && make clean

fclean:		clean
			$(RM) $(NAME) && cd libft && make fclean

re:			fclean all

.PHONY:		all clean fclean re
