SRCS = routine_bonus.c philosopher_bonus.c utils_bonus.c utils2_bonus.c utils3_bonus.c

NAME = philo_bonus

CC = gcc
FLAGS = -Wall -Werror -Wextra
TFLAG = -lpthread
RM = rm -f

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c -I ./ $< -o $@

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(OBJS) $(TFLAG) -o $(NAME)

clean:
				$(RM) $(OBJS)
fclean:         clean
				$(RM) $(NAME)  
re:             fclean all
.PHONY:         all clean fclean re