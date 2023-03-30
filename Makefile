# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 15:48:33 by marirodr          #+#    #+#              #
#    Updated: 2023/03/29 13:10:14 by marirodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS 		= 	gcc -Wall -Werror -Wextra
PRINTF 		= 	ft_printf/
LIBFT 		= 	libft/
SRCSER		=	server.c
SRCCLI		=	client.c
OBJTSER		= 	$(SRCSER:.c=.o)
OBJTCLI		= 	$(SRCCLI:.c=.o)

#@ -> Hide the executed command
#-s -> Does not print the command being executed to the console
#-C -> change the directory to the path specified by the variable before 
#      executing the command.

all: 	 $(OBJTSER) $(OBJTCLI)
	@make -s -C ${PRINTF} 
	@make -s -C ${LIBFT} 
	@${CFLAGS} libft/libft.a ft_printf/ft_printf.a $(OBJTSER) -o server
	@${CFLAGS} libft/libft.a ft_printf/ft_printf.a $(OBJTCLI) -o client
	@echo "Everything is ready"

#The pattern rule .c.o: is used to specify how to generate object files from source
#files and avoid doing relink
#The ${CFLAGS} variable is expanded to include the compilation flags, and $< is a
#shorthand for the name of the first prerequisite (in this case, the source file).
#The -c flag tells the compiler to generate an object file, and -o specifies the 
#name of the output file. ${<:.c=.o} is used to replace the .c file extension with
#.o in the output file name.

.c.o:
		@${CFLAGS} -c $< -o $@

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
