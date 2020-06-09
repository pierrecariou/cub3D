# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcariou <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/18 14:10:41 by pcariou           #+#    #+#              #
#    Updated: 2020/06/09 18:28:39 by pcariou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= Cub3D

HEADER		= ./

SRCS		=  main.c main1.c main2.c main3.c parsing.c parsing1.c parsing2.c gnl/get_next_line.c gnl/get_next_line_utils.c

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
			$(AR) $(NAME) $(OBJS) && cd libft && make

clean:
			$(RM) $(OBJS) && cd libft && make

fclean:		clean
			$(RM) $(NAME) && cd libft && make

re:			fclean all

.PHONY:		all clean fclean re
