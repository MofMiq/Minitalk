# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 13:07:27 by marirodr          #+#    #+#              #
#    Updated: 2023/03/20 16:03:02 by marirodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_printf.a

SRC			=	ft_printf.c ft_printf_tools.c ft_printf_tools2.c \

OBJT		=	$(SRC:.c=.o)

CC			= gcc -c

CFLAGS	=	-Wall -Werror -Wextra

RM			=	rm -f

all:		$(NAME)

$(NAME):
				$(CC) $(CFLAGS) $(SRC)
				ar rcs $(NAME) $(OBJT)

clean:
				$(RM) $(OBJT)

fclean:	clean
				$(RM) $(NAME)

re:			fclean all

.PHONY: all, clean, fclean, re
