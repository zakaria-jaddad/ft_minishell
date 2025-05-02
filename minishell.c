

#include "includes/minishell.h"
#include "libft/libft.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_cmd	*cmd;
	t_list	*env_lst;

        
	(void)!((void)argc, argv);
	env_lst = envs_init(env);
	if (env_lst == NULL)
		return (EXIT_FAILURE);
	while (true)
	{
		line = readline("Hello Shell >> ");
		if (line == NULL)
			break ;
		cmd = parsing(line, env_lst);
	}
	free(line);
	return (EXIT_SUCCESS);
}
