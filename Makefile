CC = cc
MAKE = make -C
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
# CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell
LIBFT_DIR = libft
MAIN = minishell.c
EXECUTION = execution/execution.c \
						execution/_cd_.c \
						execution/_exit_.c \
						execution/envs_functions.c \
						execution/sort_envs.c \
						execution/_echo_.c \
						execution/_pwd_.c \
						execution/utiles.c \
						execution/heredoc.c \
						execution/redirections.c \
						execution/handling_files.c\
						execution/signals.c
EXPANSION = parsing/expansion/expansion.c \
	    parsing/expansion/expansion_api.c \
	    parsing/expansion/get_enhanced_tokens.c \
	    parsing/expansion/dollar_expansion_utils.c \
	    parsing/expansion/dollar_expansion.c \
	    parsing/expansion/word_expansion.c \
	    parsing/expansion/wildcards/file_info.c \
	    parsing/expansion/wildcards/glob.c \
	    parsing/expansion/wildcards/shell_glob.c \
	    parsing/expansion/wildcards/shell_glob_utils.c \
	    parsing/expansion/wildcards/shell_glob_escaping_norms_1.c \
	    parsing/expansion/wildcards/shell_glob_escaping_norms_2.c \
	    parsing/expansion/wildcards/shell_glob_escaping_norms_3.c \
	    parsing/expansion/wildcards/wildcards_utils_1.c \
	    parsing/expansion/wildcards/wildcards_utils_2.c \
	    parsing/expansion/wildcards/wildcards_utils_3.c \


PARCING = ./parsing/parsing.c \
	  ./parsing/env/env.c ./parsing/env/env_utils.c \
	  ./parsing/tokenize/tokenize.c \
	  ./parsing/tokenize/tokenize_utils_1.c \
	  ./parsing/tokenize/tokenize_utils_2.c \
	  ./parsing/tokenize/tokenize_utils_3.c \
	  ./parsing/tokenize/tokenize_utils_4.c \
	  ./parsing/tokenize/tokenize_utils_5.c	\
	  ./parsing/tokenize/tokenize_utils_6.c	\
	  ./parsing/tokenize/tokenize_utils_7.c	\
	  ./parsing/tokenize/split_line.c \
	  ./parsing/tokenize/tokens_to_str.c \
	  ./parsing/pre_ast/pre_ast.c \
	  ./parsing/pre_ast/enhance_redirection.c \
	  ./parsing/ast/ast.c \
	  ./parsing/ast/get_root.c \
	  ./parsing/syntx_check/syntax_check.c \
	  $(EXPANSION)

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
