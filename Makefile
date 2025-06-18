CC = cc
MAKE = make -C
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

NAME = minishell
LIBFT_DIR = libft
MAIN = minishell.c
EXECUTION = # execution/execution.c

PARCING = ./parsing/parsing.c \
	  ./parsing/env/env.c ./parsing/env/env_utils.c \
	  ./parsing/tokenize/tokenize.c \
	  ./parsing/tokenize/tokenize_utils_1.c \
	  ./parsing/tokenize/tokenize_utils_2.c \
	  ./parsing/tokenize/tokenize_utils_3.c \
	  ./parsing/tokenize/tokenize_utils_4.c \
	  ./parsing/tokenize/split_line.c \
	  ./parsing/tokenize/pre_ast/pre_ast.c \
	  parsing/wildcards/file_info.c parsing/wildcards/glob.c parsing/wildcards/shell_glob.c parsing/wildcards/shell_glob_escaping_norms_1.c parsing/wildcards/shell_glob_escaping_norms_2.c parsing/wildcards/wildcards_utils_1.c parsing/wildcards/wildcards_utils_2.c parsing/wildcards/wildcards_utils_3.c ./parsing/wildcards/shell_glob_escaping_norms_3.c  \
	  ./parsing/ast/ast.c ./parsing/ast/ast_utils_1.c ./parsing/ast/ast_utils_2.c ./parsing/ast/ast_utils_3.c \

OBJS = $(MAIN:.c=.o) $(EXECUTION:.c=.o) $(PARCING:.c=.o)

LIBFT = libft/libft.a
INCLUDE = includes/minishell.h libft/libft.h

all : $(LIBFT) $(NAME)
	make clean

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
