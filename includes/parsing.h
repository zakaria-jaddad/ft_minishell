
#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"

typedef enum e_token_type
{
	TOKEN_NEWLINE,
	TOKEN_EOF,
	TOKEN_PAR_OPEN,
	TOKEN_PAR_CLOSE,
	TOKEN_IF_AND,
	TOKEN_IF_OR,
	TOKEN_SEMICOLON,
	TOKEN_PIPE
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

t_list				*envs_init(char **env);
t_list				*append_env(t_list **env_lst, char *key, char *value);
t_env				*get_env(t_list *env_lst, char *key);
t_env				*edit_env(t_env *env, char *new_value);
void				clear_envs(t_list **env);
void				clear_env(t_env *env);

#endif // PARSING_
