CC = cc
MAKE = make -C
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
NAME = minishell
LIBFT_DIR = libft
MAIN = minishell.c
EXECUTION = execution/execution.c
PARCING = parsing/parsing.c ./parsing/envs_init.c ./parsing/tokenizing.c ./parsing/utils/env_utils.c ./parsing/utils/split_line.c ./parsing/utils/tokenizing_utils_1.c ./parsing/utils/tokenizing_utils_2.c ./parsing/utils/tokenizing_utils_3.c
OBJS = $(MAIN:.c=.o) $(EXECUTION:.c=.o) $(PARCING:.c=.o)

LIBFT = libft/libft.a
INCLUDE = includes/minishell.h libft/libft.h

all : $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -lft -L$(LIBFT_DIR) -lreadline -o $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

clean: libft_clean 
	rm -f $(OBJS) $(OBJS:.o=.d)

fclean: libft_fclean clean
	rm -f $(NAME) $(OBJS) 

re: fclean all

$(LIBFT): libft_make

libft_make :
	$(MAKE) libft

libft_clean : 
	$(MAKE) libft clean

libft_fclean : 
	$(MAKE) libft fclean

libft_re : 
	$(MAKE) libft re

-include $(OBJS=.o:.d)
