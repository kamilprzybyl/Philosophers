FLAGS = -Wall -Wextra -Werror -lpthread
NAME = 	philo
SRC = 	src/main.c \
		src/philosophers.c \
		src/utils/ft_atoi.c \
		src/utils/print_status.c \
		src/utils/timestamp.c \
		src/utils/is_number.c \
		src/utils/ft_strlen.c \
		src/utils/ft_isdigit.c \
		src/utils/ft_usleep.c

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