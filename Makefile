# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 15:48:33 by marirodr          #+#    #+#              #
#    Updated: 2023/03/20 17:23:09 by marirodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS 		= 	gcc -Wall -Werror -Wextra
PRINTF 		= 	ft_printf/
LIBFT 		= 	libft/
SRCSER		=	server.c
SRCCLI		=	client.c
OBJTSER		= 	$(SRCSER:.c=.o)
OBJTCLI		= 	$(SRCCLI:.c=.o)
.c.o:
		@${CFLAGS} -c $< -o ${<:.c=.o}
#compila .c en el .o con el nombre del fichero de entrada(srcser, srccli)

all: 	 $(OBJTSER) $(OBJTCLI)
	@make -s -C ${PRINTF} 
	@make -s -C ${LIBFT} 
	@${CFLAGS} libft/libft.a ft_printf/ft_printf.a $(OBJTSER) -o server
	@${CFLAGS} libft/libft.a ft_printf/ft_printf.a $(OBJTCLI) -o client
	@echo "Minitalk is ready"

bonus:	all

clean:
	@make fclean -s -C ${PRINTF}
	@make fclean -s -C ${LIBFT}
	@rm -rf $(OBJTSER) $(OBJTCLI)
	@echo "Compiled objects have been removed"

fclean: clean
	@rm -f server client
	@echo "Executables have been removed"

re: fclean all

.PHONY: all bonus clean fclean re
