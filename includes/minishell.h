
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>


typedef struct s_cmd
{
	char	*foo;
}			t_cmd;

typedef struct s_env {
        char *key;
        char *value;
} t_env;


t_cmd		*parsing(char *line, t_list *env);
#endif

