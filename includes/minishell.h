#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	*foo;
}			t_cmd;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

t_cmd		*parsing(char *line, t_list *env);

t_list		*envs_init(char **env);
t_list		*append_env(t_list **env_lst, char *key, char *value);
t_env		*get_env(t_list *env_lst, char *key);
t_env		*edit_env(t_env *env, char *new_value);
void		clear_envs(t_list **env);
void		clear_env(t_env *env);
#endif
