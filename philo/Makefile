FLAGS = -Wall -Wextra -Werror
NAME = 	philo
SRC = 	main.c \
		ft_atoi.c
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