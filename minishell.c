
#include "includes/minishell.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	execution_mimic(t_cmd *cmd, t_list *env)
{
	char			*command;
	t_list			*arguments;
	t_cmd_simple	*simple_command;
        t_list *head;

	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->type == NODE_COMMAND)
	{
		simple_command = cmd->content;
		command = NULL;
		expand_command(&command, simple_command->command, env);
		printf("command = %s\n", command);
		arguments = expand_arguments(simple_command->arguments, env);
                head = arguments;
		printf("arguments: ");
		while (arguments)
		{
			printf("%s ", (char *)arguments->content);
			fflush(stdout);
			arguments = arguments->next;
		}
                free(command);
                printf("\n");
                ft_lstclear(&head, free);
	}
}

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
		print_cmd(cmd, 0);
		if (cmd == NULL)
			continue ;
		execution_mimic(cmd, env_lst);
		/* execution(cmd, env_lst); */
	}
	free(line);
	return (EXIT_SUCCESS);
}
