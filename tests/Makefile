EXEC =		test_TL
SRC =		sources/main.c \
			sources/test_TL_init.c \
			sources/test_TL_terminate.c \
			sources/test_TL_create_chart.c \
			sources/test_TL_release_chart.c \

OBJ =		$(SRC:%.c=%.o)
INC =		-I includes/ \
			-I ../includes/ \

CC =		gcc
FLAGS =		-g -Wall -Wextra

all: $(EXEC)

msg:
	@echo "\033[0;29m⌛  Making Tests : \c"

$(EXEC): msg $(OBJ)
	@echo ""
	@gcc -o $(EXEC) $(OBJ) ../TL.a
	@echo "\033[0;34m✅  Executable created !\033[0;29m"

sources/%.o: sources/%.c
	@$(CC) $(FLAGS) -o $@ -c $< $(INC)
	@echo "\033[0;32m.\c\033[0;29m"

clean:
	@echo "\033[0;31m🔥  Cleaning Tests Objects...\033[0;29m"
	@rm -rf $(OBJ)

fclean: clean
	@echo "\033[0;31m🔥  Cleaning Tests Executable...\033[0;29m"
	@rm -rf $(EXEC)

re: fclean all

.PHONY: all clean fclean re msg
