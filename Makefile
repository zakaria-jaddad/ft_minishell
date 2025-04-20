CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline
NAME = minishell
MAIN = minishell.c
EXECUTION = execution/
PARCING = parcing/
OBJS = $(MAIN=.c:.o) $(EXECUTION=.c:.o) $(PARCING:.c=.o)

all : $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -MMD

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

-include $(OBJS=.o:.d)
