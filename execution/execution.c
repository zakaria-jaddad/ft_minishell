/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:56:52 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/29 10:40:16 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*valid_command(char *cmd, char *path)
{
	char	*rv;
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		rv = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(rv, X_OK))
		{
			break ;
		}
		free(rv);
		rv = NULL;
		i++;
	}
	free_double_pointer((void **)paths);
	if (rv)
		return (rv);
	return (ft_strdup(cmd));
}

// TODO: USE errno to get the err status and print its error :))
int	display_execve_error(char *command)
{
	if (errno == ENOENT)
	{
		if (ft_strnstr(command, "/", ft_strlen(command)))
			return (ft_fprintf(2, "minishell: %s: No such file or directory\n",
					command), 127);
		else
			return (ft_fprintf(2, "minishell: %s: Command not found\n",
					command), 127);
	}
	if (errno == EISDIR)
		return (ft_fprintf(2, "minishell: %s: Is a directory\n", command), 126);
	if (errno == ENOEXEC)
		return (ft_fprintf(2, "minishell: %s: Exec format error\n", command),
			126);
	if (errno == ENOMEM)
		return (ft_fprintf(2, "minishell: %s: Cannot allocate memory\n",
				command), 1);
	if (errno == EFAULT)
		return (ft_fprintf(2, "minishell: %s: Bad address\n", command), 1);
	if (errno == ENOTDIR)
		return (ft_fprintf(2, "minishell: %s: Not a directory\n", command), 1);
	return (ft_fprintf(2, "minishell: %s: %s\n", command, strerror(errno)), 1);
}
int	not_builtin(t_cmd_simple *tree, t_list *env_list)
{
	pid_t	pid;
	char	**envs;
	char	**args;
	char	*path;
	char	*cmd;
	int		status;

	if (get_env(env_list, "PATH") && get_env(env_list, "PATH")->value)
	{
		pid = fork();
		if (pid < 0)
			return (ft_fprintf(2, "fork failed\n"), 1);
		if (pid == 0)
		{
			if (signal(SIGINT, handle_ctrC_fork) == SIG_ERR)
				ft_fprintf(STDERR_FILENO, "signal: error handling ctr+c!!\n");
			envs = envs_list_to_double_pointer(env_list);
			if (!envs)
				return (0);
			args = list_to_double_pointer(expand_arguments(tree->arguments,
						env_list));
			args = arr_add_front(list_to_double_pointer(expand_command(tree->command,
							env_list)), args);
			if (!args)
			{
				ft_fprintf(2, "minishell: : Command not found\n");
				exit(127);
			}
			cmd = args[0];
			path = valid_command((char *)cmd, get_env(env_list, "PATH")->value);
			if (execve(path, args, envs) < 0)
			{
				free(path);
				// perror("error");
				exit(display_execve_error(cmd));
			}
			free(path);
			free_double_pointer((void **)args);
			free_double_pointer((void **)envs);
			exit(0);
		}
		else
		{
			wait(&status);
			status_x(WEXITSTATUS(status), 1);
		}
	}
	else
		return (1);
	return (0);
}

int	execution_simple_commad(t_cmd_simple *cmd, t_list *envs)
{
	char	**args;

	args = list_to_double_pointer(expand_arguments(cmd->arguments, envs));
	if (ft_strcmp(tokens_to_str(cmd->command), "cd") == 0)
		return (_cd_(envs, args));
	if (ft_strcmp(tokens_to_str(cmd->command), "export") == 0)
		return (_export_(envs, args));
	if (ft_strcmp(tokens_to_str(cmd->command), "env") == 0)
		return (_env_(envs));
	if (ft_strcmp(tokens_to_str(cmd->command), "echo") == 0)
		return (_echo_(args), 0);
	if (ft_strcmp(tokens_to_str(cmd->command), "pwd") == 0)
		return (_pwd_(manage_pwd(NULL)));
	if (ft_strcmp(tokens_to_str(cmd->command), "unset") == 0)
		return (_unset_(envs, args), 0);
	if (ft_strcmp(tokens_to_str(cmd->command), "exit") == 0)
	{
		_exit_(args);
	}
	return (free_double_pointer((void **)args), not_builtin(cmd, envs));
}

int	execution(t_cmd *tree, t_list *env_list)
{
	if (!tree || !env_list)
		return (1);
	setup_pwd(get_env(env_list, "PWD"));
	if (tree->type == NODE_IF_AND)
	{
		status_x(execution(tree->left, env_list), 1);
		return (execution(tree->right, env_list));
	}
	else if (tree->type == NODE_IF_OR)
	{
		if (execution(tree->left, env_list))
			return (execution(tree->right, env_list));
		return (0);
	}
	else if (tree->type == NODE_PIPE)
	{
		return (run_in_pipe(tree, env_list));
	}
	else if (tree->type == NODE_IN_REDIR || tree->type == NODE_HEREDOC
		|| tree->type == NODE_OUT_REDIR || tree->type == NODE_APPEND_REDIR)
	{
		return (run_redir(tree, env_list));
	}
	return (execution_simple_commad(tree->content, env_list));
}
