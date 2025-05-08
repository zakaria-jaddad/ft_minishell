
#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>

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
	char			*foo;
}					t_cmd;

t_cmd				*parsing(char *line, t_list *env);

// envs
t_list				*envs_init(char **env);
t_list				*append_env(t_list **env_lst, char *key, char *value);
t_env				*get_env(t_list *env_lst, char *key);
t_env				*edit_env(t_env *env, char *new_value);
void				clear_envs(t_list **env);
void				clear_env(t_env *env);

// Tokenizing
t_list				*split_line(char *line);
void				free_token(t_token *token);
void				free_tokens(t_list **tokens);
void				append_str(char **token_data, char *new_data);
void				append_last_toke_data(t_list **tokens, char *new_data);
bool				check_equal_in_last_token(t_list *tokens);
bool				is_last_token_type_word(t_list *tokens);
bool				is_token_type_word(t_list *node);
t_list				*create_token_node(t_token_type token_type,
						char *token_data);
t_list				*tokenize_quotes(char *quote_type, t_token_type token_type,
						t_list **line_lst);
t_list				*get_tokens(char *line);
t_list				*get_token_node(t_list *line_lst);
t_token				*create_token(t_token_type token_type, char *token_data);

char				*get_token_type(t_token_type token);

#endif // PARSING_
