
#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <dirent.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

# define NOTNULL ((void *)0x1)

typedef enum e_token_type
{
	TOKEN_PAR_OPEN,     // (
	TOKEN_PAR_CLOSE,    // )
	TOKEN_PIPE,         // |
	TOKEN_IN_REDIR,     // <
	TOKEN_OUT_REDIR,    // >
	TOKEN_IF_AND,       // &&
	TOKEN_IF_OR,        // ||
	TOKEN_HEREDOC,      // <<
	TOKEN_APPEND_REDIR, // >>
	TOKEN_WHITE_SPACE,  // \t " "
	TOKEN_WORD,         //
	TOKEN_DOUBLE_QUOTE_WORD,
	TOKEN_SINGLE_QUOTE_WORD,
	TOKEN_COMMAND
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*data;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_cmd
{
	t_list			*command; // list of current command tokens
	t_token_type	type; // type of the current command
	struct s_cmd	*left;
	struct s_cmd	*right;
	t_list			*arguments;
	t_list			*infile;
	t_list			*outfile;
}					t_cmd;
t_cmd				*parsecmd(char *line, t_list *env);

// envs
t_list				*envs_init(char **env);
t_list				*append_env(t_list **env_lst, char *key, char *value);
t_env				*get_env(t_list *env_lst, char *key);
t_env				*edit_env(t_env *env, char *new_value);
void				free_env(void *env);

// Tokenizing
t_list				*split_line(char *line);
void				print_split(t_list *line_lst);
void				print_tokens(t_list *tokens);
void				free_token(void *token);
void				append_str(char **current_data, char *to_append);
bool				check_equal_in_last_token(t_list *tokens);
bool				is_last_token_type_space(t_list *tokens);
t_list				*create_token_node(t_token_type token_type,
						char *token_data);
t_list				*tokenize_quotes(char *quote_type, t_token_type token_type,
						t_list **line_lst);
t_list				*gettokens(char *line);
t_list				*get_token_node(t_list *line_lst);
t_token				*create_token(t_token_type token_type, char *token_data);
char				*get_token_type(t_token_type token);

/*
 * @brief hold file information
 * s_file_info is used when expanding "*" wildcards
 * file_name a string allocated in the heap memory
 */
typedef struct s_file_info
{
	unsigned char	file_type;
	char			*file_name;
}					t_file_info;

t_file_info			*creat_file_info(unsigned char file_type, char *file_name);
t_list				*creat_file_node(unsigned char file_type, char *file_name);
char				*get_file_type(unsigned char file_type);
void				print_dir_content(t_list *dir_content);
void				free_file_info(void *file_info);
void				append_file_name(t_list **matches, char *file_name,
						char *path);

// Expanding Wildcards
t_list				*expand_wildcard(char *str);
char				*join_lst(t_list *lst);
char				*get_cwd_name(void);
char				*get_dir_path(t_list *lst);
t_list				*get_dir_content(char *dirname);
bool				is_valid_absolute_path(char *str);
t_list				*sgen(char *p, t_list *pa, t_list *nm, t_list *m);
void				*init_pattern_and_matches(char **pattern, t_list **matches,
						t_list *patterns, char *path);
void				*init_new_path_and_fi(char **new_path, char *path,
						t_file_info **fi, t_file_info *matches_content);
void				*clear_new_matches_and_matches(t_list **new_matches,
						t_list **matches);
void				append_file_name_to_path(char **path, char *file_name);
void				*nmmt(t_list **matches_tmp, t_list **new_matches,
						t_list **matches);
bool				is_dir_with_trailing_slash(t_file_info *file_info,
						t_list *patterns);
bool				is_regfile_with_slash(t_file_info *file_info,
						t_list *patterns);
bool				is_valid_next_pattern(t_list *patterns);
bool				is_valid_glob(char *pattern, t_file_info *fi);
bool				glob(const char *pattern, const char *text);
void				check_glob(const char *pattern, const char *text);
void				remove_path(t_list *matches, char *pattern);
void				sort_matches(t_list **matches);

inline void	panic(char *s)
{
	ft_fprintf(STDERR_FILENO, s);
	exit(EXIT_FAILURE);
}

// ast
t_list	*get_root(t_list *tokens);

#endif // PARSING_
