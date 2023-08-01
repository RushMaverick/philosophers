NAME 		= philo

S			= src
O			= obj
INCLUDES = inc

SRC = \
$S/main.c		$S/mutex.c			$S/errors.c			$S/utils.c		$S/philo.c		\
$S/governor.c	$S/philo_actions.c	$S/philo_utils.c	$S/attr.c		$S/printing.c
OBJ			= $(patsubst $S/%,$O/%,$(SRC:.c=.o))

HEADER = inc/philosophers.h
CFLAGS = -Wall -Wextra -Werror -pthread -O3

####

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	cc $(CFLAGS) -I$(INCLUDES) $(OBJ) -o $(NAME)

$O:
	@mkdir $@

$O/%.o: $S/%.c $(HEADER) | $O
	cc $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	rm -rf $O

fclean: clean
	rm -f $(NAME)

re: fclean all
