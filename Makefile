LIB =		TL.a
SRC =		sources/indicators/ema.c \
			sources/indicators/ma.c \
			sources/indicators/average.c \
			sources/init.c \

OBJ =		$(SRC:%.c=%.o)
INC =		-I includes/
CC =		gcc
FLAGS =		-O3 -std=c99 -Wall -Wextra

all: $(LIB)

msg:
	@echo "\033[0;29m⌛  Making Library : \c"

$(LIB): msg $(OBJ)
	@echo ""
	@ar rcs $(LIB) $(OBJ)
	@ranlib $(LIB)
	@echo "\033[0;34m✅  Executable created !\033[0;29m"

tests:
	@make
	@make -C tests
	@./tests/test_TL

sources/%.o: sources/%.c
	@$(CC) $(FLAGS) -o $@ -c $< $(INC)
	@echo "\033[0;32m.\c\033[0;29m"

clean:
	@echo "\033[0;31m🔥  Cleaning Library Objects...\033[0;29m"
	@rm -rf $(OBJ)
	@make clean -C tests

fclean: clean
	@echo "\033[0;31m🔥  Cleaning Library Executable...\033[0;29m"
	@rm -rf $(LIB)
	@make fclean -C tests

re: fclean all

.PHONY: all clean fclean re msg tests
