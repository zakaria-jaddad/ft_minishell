CC = cc
MAKE = make -C
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
LIBFT_DIR = libft
MAIN = minishell.c
EXECUTION = execution/execution.c
PARCING = parsing/parsing.c
OBJS = $(MAIN:.c=.o) $(EXECUTION:.c=.o) $(PARCING:.c=.o)

all : $(NAME)


$(NAME): libft_all $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lft -L$(LIBFT_DIR) -lreadline -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

clean: libft_clean
	rm -f $(OBJS) $(OBJS:.o=.d)

fclean: libft_fclean clean
	rm -f $(NAME) $(OBJS) 

re: fclean all

libft_all : 
	$(MAKE) libft

libft_clean : 
	$(MAKE) libft clean

libft_fclean : 
	$(MAKE) libft fclean

libft_re : 
	$(MAKE) libft re

-include $(OBJS=.o:.d)
