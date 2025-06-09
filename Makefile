CC = cc
MAKE = make -C
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

NAME = minishell
LIBFT_DIR = libft
MAIN = minishell.c
<<<<<<< HEAD
EXECUTION = execution/_cd_.c execution/_echo_.c execution/envs_functions.c execution/execution.c execution/_exit_.c execution/expend_string.c execution/_pwd_.c execution/sort_envs.c execution/utiles.c
PARCING = parsing/parsing.c ./parsing/envs_init.c ./parsing/tokenizing.c ./parsing/utils/env_utils.c ./parsing/utils/split_line.c ./parsing/utils/tokenizing_utils_1.c ./parsing/utils/tokenizing_utils_2.c ./parsing/utils/tokenizing_utils_3.c
=======
EXECUTION = execution/execution.c
PARCING = parsing/parsing.c ./parsing/envs_init.c ./parsing/tokenizing.c ./parsing/utils/env_utils.c ./parsing/utils/split_line.c ./parsing/utils/tokenizing_utils_1.c ./parsing/utils/tokenizing_utils_2.c ./parsing/utils/tokenizing_utils_3.c parsing/utils/wildcards/file_info.c parsing/utils/wildcards/glob.c parsing/utils/wildcards/shell_glob.c parsing/utils/wildcards/shell_glob_escaping_norms_1.c parsing/utils/wildcards/shell_glob_escaping_norms_2.c parsing/utils/wildcards/wildcards_utils_1.c parsing/utils/wildcards/wildcards_utils_2.c parsing/utils/wildcards/wildcards_utils_3.c ./parsing/utils/wildcards/shell_glob_escaping_norms_3.c  ./parsing/get_root.c
>>>>>>> ef2d27c32e4c8ec17747ae25d272961ffca00c91
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
