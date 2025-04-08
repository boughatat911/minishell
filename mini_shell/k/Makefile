NAME = parser_test

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I.
LDFLAGS = -L/opt/homebrew/opt/readline/lib
CPPFLAGS = -I/opt/homebrew/opt/readline/include
LDLIBS = -lreadline

SRCS = main.c tokenizer.c parser.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 