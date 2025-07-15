/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:35:57 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/14 22:33:10 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	execve_fork(char **args, t_list *env_list, char *path)
{
	char	**envs;

	signal(SIGQUIT, SIG_DFL);
	if (signal(SIGINT, handle_ctr_c_fork) == SIG_ERR)
		ft_fprintf(STDERR_FILENO, "signal: error: ctr+c!!\n");
	if (!args)
		write(2, "minishell:  command not found\n", 30);
	if (!args)
		exit(-1);
	envs = envs_list_to_double_pointer(env_list);
	if (!envs)
		exit(1);
	if (get_env(env_list, "PATH") && get_env(env_list, "PATH")->value)
		path = valid_command(args[0], get_env(env_list, "PATH")->value);
	else
		path = ft_strdup(args[0]);
	if (!ft_strnstr(path, "/", ft_strlen(path)))
		return (ft_fprintf(2, "minishell: %s: Command not found\n", path),
			exit(127));
	if (execve(path, args, envs) < 0)
		return (free(path), exit(display_execve_error(args[0])));
	free(path);
	free_double_pointer((void **)args);
	free_double_pointer((void **)envs);
	exit(0);
}

int	not_builtin(char **args, t_list *env_list)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
		return (ft_fprintf(2, "fork failed\n"), 1);
	if (pid == 0)
		execve_fork(args, env_list, "");
	else
	{
		wait(&status);
		if (WEXITSTATUS(status))
			status_x((unsigned char)(WEXITSTATUS(status)), 1);
		else if (WIFSIGNALED(status))
			status_x((unsigned char)(128 + status), 1);
		else
			status_x(0, 1);
	}
	return (status_x(0, 0));
}

int	execution_simple_command(t_cmd_simple *cmd, t_list **envs)
{
	char	**args;
	int		status;

	args = expand_all(cmd->command, cmd->arguments, *envs);
	status = 0;
	if (!args)
		return (0);
	else if (ft_strcmp(args[0], "cd") == 0)
		status = _cd_(*envs, args + 1);
	else if (ft_strcmp(args[0], "export") == 0)
		status = _export_(*envs, args + 1);
	else if (ft_strcmp(args[0], "env") == 0)
		status = _env_(*envs, args + 1);
	else if (ft_strcmp(args[0], "echo") == 0)
		status = _echo_(args + 1);
	else if (ft_strcmp(args[0], "pwd") == 0)
		status = _pwd_(manage_pwd(NULL));
	else if (ft_strcmp(args[0], "unset") == 0)
		status = _unset_(envs, args + 1);
	else if (ft_strcmp(args[0], "exit") == 0)
		return (_exit_(args + 1), status_x(0, 0));
	else
		status = (not_builtin(args, *envs), status_x(0, 0));
	free_double_pointer((void **)args);
	return (status_x(status, 1));
}

int	execution(t_cmd *tree, t_list **env_list)
{
	if (!tree || !env_list)
		return (1);
	setup_pwd(get_env(*env_list, "PWD"));
	if (tree->type == NODE_IF_AND)
	{
		if (status_x(execution(tree->left, env_list), 1) == 0)
			return (execution(tree->right, env_list));
		return (status_x(0, 0));
	}
	else if (tree->type == NODE_IF_OR)
	{
		if (execution(tree->left, env_list))
			return (execution(tree->right, env_list));
		return (0);
	}
	else if (tree->type == NODE_PIPE)
	{
		return (run_in_pipe(tree, *env_list));
	}
	else if (tree->type == NODE_IN_REDIR || tree->type == NODE_HEREDOC
		|| tree->type == NODE_OUT_REDIR || tree->type == NODE_APPEND_REDIR)
	{
		return (run_redir(tree, *env_list));
	}
	return (execution_simple_command(tree->content, env_list));
}
