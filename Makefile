# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/19 12:34:44 by tjarross          #+#    #+#              #
#    Updated: 2018/08/15 12:54:30 by tjarross         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB =		ta_lib.a
SRC =		sources/indicators/ma.c \
			sources/init.c \

OBJ =		$(SRC:%.c=%.o)
INC =		-I includes/
CC =		gcc
FLAGS =		-O3 -Wall -Wextra

all: $(LIB)

msg:
	@echo "\033[0;29m⌛  Making Library : \c"

$(LIB): msg $(OBJ)
	@echo ""
	@ar rcs $(LIB) $(OBJ)
	@ranlib $(LIB)
	@echo "\033[0;34m✅  Executable created !\033[0;29m"

sources/%.o: sources/%.c
	@$(CC) $(FLAGS) -o $@ -c $< $(INC)
	@echo "\033[0;32m.\c\033[0;29m"

clean:
	@echo "\033[0;31m🔥  Cleaning Library Objects...\033[0;29m"
	@rm -rf $(OBJ)

fclean: clean
	@echo "\033[0;31m🔥  Cleaning Library Executable...\033[0;29m"
	@rm -rf $(LIB)

re: fclean all

.PHONY: all clean fclean re msg
