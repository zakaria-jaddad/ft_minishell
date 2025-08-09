CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = ft_minishell
MAIN = ft_minishell.c

LIBFT = ./libft/ft_add_node.c \
	./libft/ft_atoi.c \
	./libft/ft_bzero.c \
	./libft/ft_calloc.c \
	./libft/ft_fprintf/ft_fprintf.c \
	./libft/ft_fprintf/ft_fprintf_put_unsigned_nbr_fd.c \
	./libft/ft_fprintf/ft_fprintf_putaddress_fd.c \
	./libft/ft_fprintf/ft_fprintf_putchar_fd.c \
	./libft/ft_fprintf/ft_fprintf_puthex_fd.c \
	./libft/ft_fprintf/ft_fprintf_putnbr_fd.c \
	./libft/ft_fprintf/ft_fprintf_putstr_fd.c \
	./libft/ft_fprintf/ft_fprintf_strlen.c \
	./libft/ft_isdigit.c \
	./libft/ft_itoa.c \
	./libft/ft_lst_rm_one.c \
	./libft/ft_lstadd_back_bonus.c \
	./libft/ft_lstadd_front_bonus.c \
	./libft/ft_lstclear_bonus.c \
	./libft/ft_lstdelone_bonus.c \
	./libft/ft_lstfirst_bonus.c \
	./libft/ft_lstlast_bonus.c \
	./libft/ft_lstnew_bonus.c \
	./libft/ft_lstsize_bonus.c \
	./libft/ft_memcpy.c \
	./libft/ft_memset.c \
	./libft/ft_split.c \
	./libft/ft_split_pro.c \
	./libft/ft_split_pro_max.c \
	./libft/ft_strchr.c \
	./libft/ft_strcmp.c \
	./libft/ft_strdup.c \
	./libft/ft_strjoin.c \
	./libft/ft_strlcat.c \
	./libft/ft_strlcpy.c \
	./libft/ft_strlen.c \
	./libft/ft_strncmp.c \
	./libft/ft_strnstr.c \
	./libft/ft_strpbrk.c \
	./libft/ft_substr.c \
	./libft/ft_tolower.c \

EXECUTION = execution/execution.c \
	    execution/_cd_.c \
	    execution/_exit_.c \
	    execution/envs_functions.c \
	    execution/sort_envs.c \
	    execution/_echo_.c \
	    execution/_pwd_.c \
	    execution/utiles.c \
	    execution/redirections.c \
	    execution/handling_files.c\
	    execution/signals.c \
	    execution/helpers.c \
	    execution/list_management.c \
	    execution/unset.c \
	    execution/export.c \
	    execution/errors.c \
	    execution/redir_helpers.c \

EXPANSION = ./parsing/expansion/dollar_expansion.c \
	    ./parsing/expansion/dollar_expansion_utils.c \
	    ./parsing/expansion/expand_word.c \
	    ./parsing/expansion/expand_word_utils.c \
	    ./parsing/expansion/expansion.c \
	    ./parsing/expansion/expansion_utils.c \
	    ./parsing/expansion/expansion_api.c \
	    ./parsing/expansion/get_enhanced_tokens.c \
	    ./parsing/expansion/get_word_tokens.c \
	    ./parsing/expansion/is_assignment_statement.c \
	    ./parsing/expansion/pre_expansion.c \
	    ./parsing/expansion/pre_expansion_utils_1.c \
	    ./parsing/expansion/word_expansion.c \
	    ./parsing/expansion/wildcards/file_info.c \
	    ./parsing/expansion/wildcards/glob.c \
	    ./parsing/expansion/wildcards/shell_glob.c \
	    ./parsing/expansion/wildcards/shell_glob_escaping_norms_1.c \
	    ./parsing/expansion/wildcards/shell_glob_escaping_norms_2.c \
	    ./parsing/expansion/wildcards/shell_glob_escaping_norms_3.c \
	    ./parsing/expansion/wildcards/shell_glob_utils.c \
	    ./parsing/expansion/wildcards/wildcards_utils_1.c \
	    ./parsing/expansion/wildcards/wildcards_utils_2.c \
	    ./parsing/expansion/wildcards/wildcards_utils_3.c \

SYNTAX_CHECK = 	  ./parsing/syntx_check/syntax_check.c \
		  ./parsing/syntx_check/syntax_check_utils_1.c \
		  ./parsing/syntx_check/par_check.c \
		  ./parsing/syntx_check/check_pipe.c \
		  ./parsing/syntx_check/check_redir.c \
		  ./parsing/syntx_check/check_logical.c \

AST = ./parsing/ast/ast.c \
      ./parsing/ast/get_root.c \
      ./parsing/ast/ast_utils.c \
      ./parsing/ast/free_ast.c \

PRE_AST = ./parsing/pre_ast/pre_ast.c \
	  ./parsing/pre_ast/enhance_redirection.c \
	  ./parsing/pre_ast/heredoc.c \
	  ./parsing/pre_ast/heredoc_utils.c \

TOKENIZE = ./parsing/tokenize/tokenize.c \
	   ./parsing/tokenize/tokenize_utils_1.c \
	   ./parsing/tokenize/tokenize_utils_2.c \
	   ./parsing/tokenize/tokenize_utils_3.c \
	   ./parsing/tokenize/tokenize_utils_4.c \
	   ./parsing/tokenize/tokenize_utils_5.c	\
	   ./parsing/tokenize/tokenize_utils_6.c	\
	   ./parsing/tokenize/tokenize_utils_7.c	\
	   ./parsing/tokenize/tokenize_utils_8.c	\
	   ./parsing/tokenize/split_line.c \
	   ./parsing/tokenize/tokens_to_str.c \

ENV = ./parsing/env/env.c \
      ./parsing/env/env_utils.c \

PARCING = ./parsing/parsing.c $(ENV) $(TOKENIZE) $(EXPANSION) $(SYNTAX_CHECK) $(AST) $(PRE_AST)

OBJS = $(MAIN:.c=.o) $(EXECUTION:.c=.o) $(PARCING:.c=.o) $(LIBFT:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

clean:  
	rm -f $(OBJS) $(OBJS:.o=.d)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(OBJS:.o=.d)
