
#ifndef PARSING_H
# define PARSING_H

# include "../../libft/libft.h"
# include "ast.h"
# include "env.h"
# include "expansion.h"
# include "file_info.h"
# include "pre_ast.h"
# include "tokenize.h"
# include <dirent.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

#define SYNTAX_E "bash: syntax error near unexpected token `%s'\n"

bool	syntax_check(t_list *tokens);
t_cmd	*parse_cmd(char *line, t_list *env);
void	clear_cmd(t_cmd *cmd);

#endif // PARSING_H
