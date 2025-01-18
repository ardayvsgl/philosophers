SRCS = routine.c philosophers.c utils.c utils2.c utils3.c

NAME = philo

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
