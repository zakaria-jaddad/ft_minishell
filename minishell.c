
#include "includes/minishell.h"
#include "libft/libft.h"
#include <includes/parsing/parsing.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	main(int _, char **__, char **env)
{

	char	*line;
	t_cmd	*cmd;
	t_list	*env_lst;

	env_lst = envs_init(env, _, __);
	if (env_lst == NULL)
		return (EXIT_FAILURE);
	// Register signal handler for SIGINT (Ctrl+C)
	if (signal(SIGINT, handle_ctr_c) == SIG_ERR)
	{
		ft_fprintf(STDERR_FILENO, "signal: error handling ctr+c!!\n");
		return (1);
	}
	if (!isatty(0) && !isatty(1))
		return (0);
	while (true)
	{
		signals_handling();
		line = readline("ft_minishell -> ");
		if (line == NULL)
			(ft_lstclear(&env_lst, free_env), _exit_(NULL));
		// TODO: SKIP SPACES 
		if (*line)
			add_history(line);
		cmd = parse_cmd(line, env_lst);
		if (cmd == NULL)
		{
			line = (free(line), NULL);
			continue ;
		}
		print_cmd(cmd, 0);
		execution(cmd, env_lst);
		clear_cmd(cmd);
		line = (free(line), NULL);
	}
	free(line);
	return (EXIT_SUCCESS);
}
