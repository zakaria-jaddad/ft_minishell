
#include "includes/minishell.h"
#include "libft/libft.h"
#include <stdlib.h>

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
	};
	while (true)
	{
		line = readline("ft_minishell -> ");
		if (line == NULL)
			_exit_(NULL);
		if (*line)
			add_history(line);
		cmd = parse_cmd(line, env_lst);
		if (cmd == NULL)
			continue ;
		// print_cmd(cmd, 0);
		// printf("%s\n",
		// char *command;
		// char **arguments;
		// list_to_string(((t_cmd_simple *)cmd->content)->command));
		// print_tokens_data(((t_cmd_simple *)cmd->content)->command);
		// expand_simple_cmd(&command, &arguments,
		// (t_cmd_simple *)cmd->content);
		// printf("cmd: %s\n", command);
		// printf("args1: %s\n", arguments[0]);
		// printf("args2: %s\n", arguments[1]);
		execution(cmd, env_lst);
		// printf("$?: %d\n", status_x(0, 0));
	}
	free(line);
	return (EXIT_SUCCESS);
}
