├── Makefile
├── execution
    ├── _cd_.c
    ├── _echo_.c
    ├── _exit_.c
    ├── _pwd_.c
    ├── envs_functions.c
    ├── errors.c
    ├── execution.c
    ├── export.c
    ├── handling_files.c
    ├── helpers.c
    ├── list_management.c
    ├── redir_helpers.c
    ├── redirections.c
    ├── signals.c
    ├── sort_envs.c
    ├── unset.c
    └── utiles.c
├── ft_minishell.c
├── includes
    ├── execution.h
    ├── minishell.h
    └── parsing
    │   ├── ast.h
    │   ├── env.h
    │   ├── expansion.h
    │   ├── file_info.h
    │   ├── parsing.h
    │   ├── pre_ast.h
    │   ├── syntax_check.h
    │   └── tokenize.h
├── libft
    ├── ft_add_node.c
    ├── ft_atoi.c
    ├── ft_bzero.c
    ├── ft_calloc.c
    ├── ft_fprintf
    │   ├── ft_fprintf.c
    │   ├── ft_fprintf_put_unsigned_nbr_fd.c
    │   ├── ft_fprintf_putaddress_fd.c
    │   ├── ft_fprintf_putchar_fd.c
    │   ├── ft_fprintf_puthex_fd.c
    │   ├── ft_fprintf_putnbr_fd.c
    │   ├── ft_fprintf_putstr_fd.c
    │   └── ft_fprintf_strlen.c
    ├── ft_isdigit.c
    ├── ft_itoa.c
    ├── ft_lst_rm_one.c
    ├── ft_lstadd_back_bonus.c
    ├── ft_lstadd_front_bonus.c
    ├── ft_lstclear_bonus.c
    ├── ft_lstdelone_bonus.c
    ├── ft_lstfirst_bonus.c
    ├── ft_lstlast_bonus.c
    ├── ft_lstnew_bonus.c
    ├── ft_lstsize_bonus.c
    ├── ft_memcpy.c
    ├── ft_memset.c
    ├── ft_split.c
    ├── ft_split_pro.c
    ├── ft_split_pro_max.c
    ├── ft_strchr.c
    ├── ft_strcmp.c
    ├── ft_strdup.c
    ├── ft_strjoin.c
    ├── ft_strlcat.c
    ├── ft_strlcpy.c
    ├── ft_strlen.c
    ├── ft_strncmp.c
    ├── ft_strnstr.c
    ├── ft_strpbrk.c
    ├── ft_substr.c
    ├── ft_tolower.c
    └── libft.h
└── parsing
    ├── .media
        └── tree-evaluate.png
    ├── README.md
    ├── ast
        ├── ast.c
        ├── ast_utils.c
        ├── free_ast.c
        └── get_root.c
    ├── env
        ├── env.c
        └── env_utils.c
    ├── expansion
        ├── dollar_expansion.c
        ├── dollar_expansion_utils.c
        ├── expand_word.c
        ├── expand_word_utils.c
        ├── expansion.c
        ├── expansion_api.c
        ├── expansion_utils.c
        ├── get_enhanced_tokens.c
        ├── get_word_tokens.c
        ├── is_assignment_statement.c
        ├── pre_expansion.c
        ├── pre_expansion_utils_1.c
        ├── wildcards
        │   ├── file_info.c
        │   ├── glob.c
        │   ├── shell_glob.c
        │   ├── shell_glob_escaping_norms_1.c
        │   ├── shell_glob_escaping_norms_2.c
        │   ├── shell_glob_escaping_norms_3.c
        │   ├── shell_glob_utils.c
        │   ├── wildcards_utils_1.c
        │   ├── wildcards_utils_2.c
        │   └── wildcards_utils_3.c
        └── word_expansion.c
    ├── parsing.c
    ├── pre_ast
        ├── enhance_redirection.c
        ├── heredoc.c
        ├── heredoc_utils.c
        └── pre_ast.c
    ├── syntx_check
        ├── check_logical.c
        ├── check_pipe.c
        ├── check_redir.c
        ├── par_check.c
        ├── syntax_check.c
        └── syntax_check_utils_1.c
    └── tokenize
        ├── split_line.c
        ├── tokenize.c
        ├── tokenize_utils_1.c
        ├── tokenize_utils_2.c
        ├── tokenize_utils_3.c
        ├── tokenize_utils_4.c
        ├── tokenize_utils_5.c
        ├── tokenize_utils_6.c
        ├── tokenize_utils_7.c
        ├── tokenize_utils_8.c
        └── tokens_to_str.c
