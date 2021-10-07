FLAGS = -Wall -Wextra -Werror -lpthread
NAME = 	philo
SRC = 	main.c \
		philosophers.c \
		utils/ft_atoi.c \
		utils/print_status.c \
		utils/timestamp.c
OBJ = 	$(SRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -o $@

clean:
	rm -fr $(OBJ)

fclean:
	make clean
	rm -fr $(NAME)

re: fclean all