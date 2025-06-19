
#ifndef PARSING_H
# define PARSING_H

# include "../../libft/libft.h"
# include "env.h"
# include "tokenize.h"
# include "wildcards.h"
# include "ast.h"
# include "file_info.h"
# include "pre_ast.h"
# include <dirent.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

# define NOTNULL ((void *)0x1)

bool				syntax_check(t_list **tokens);
t_cmd				*parse_cmd(char *line, t_list *env);

static inline void	panic(char *s)
{
	ft_fprintf(STDERR_FILENO, s);
	exit(EXIT_FAILURE);
}

#endif // PARSING_H
