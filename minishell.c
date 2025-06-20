

#include "includes/minishell.h"
#include "includes/parsing/ast.h"

int	main(int _, char **__, char **env)
{
	char	*line;
	t_cmd	*cmd;
	t_list	*env_lst;

        
	env_lst = envs_init(env, _, __);
	if (env_lst == NULL)
		return (EXIT_FAILURE);
	while (true)
	{
		line = readline("Hello Shell >> ");
		if (line == NULL)
			break ;
		cmd = parse_cmd(line, env_lst);
                if (cmd == NULL)
                        continue ;
                print_cmd(cmd, 0);
	}
	free(line);
	return (EXIT_SUCCESS);
}
