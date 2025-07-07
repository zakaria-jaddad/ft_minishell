/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:35:57 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/05 18:28:13 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>

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

int	display_execve_error(char *command)
{
	if (errno == ENOENT || errno == EACCES)
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

void	execve_fork(char **args, t_list *env_list, char *path)
{
	char	**envs;

	if (signal(SIGINT, handle_ctr_c_fork) == SIG_ERR)
		ft_fprintf(STDERR_FILENO, "signal: error: ctr+c!!\n");
	envs = envs_list_to_double_pointer(env_list);
	if (!envs)
		exit(1);
	if (!args)
		ft_fprintf(2, "minishell: : Command not found\n");
	if (!args)
		exit(127);
	path = valid_command(args[0], get_env(env_list, "PATH")->value);
	if (execve(path, args, envs) < 0)
	{
		free(path);
		exit(display_execve_error(args[0]));
	}
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
	if (get_env(env_list, "PATH") && get_env(env_list, "PATH")->value)
	{
		pid = fork();
		if (pid < 0)
			return (ft_fprintf(2, "fork failed\n"), 1);
		if (pid == 0)
			execve_fork(args, env_list, "");
		else
		{
			wait(&status);
			if (status)
				status_x(130, 1);
			else
				status_x(0, 1);
		}
	}
	else
		return (1);
	return (status);
}

int	execution_simple_command(t_cmd_simple *cmd, t_list *envs)
{
	char	**args;
	int		status;
	int		ret;

	args = expand_all(cmd->command, cmd->arguments, envs);
	status = 0;
	if (!args)
		return (status);
	else if (ft_strcmp(args[0], "cd") == 0)
		status = _cd_(envs, args + 1);
	else if (ft_strcmp(args[0], "export") == 0)
		status = _export_(envs, args + 1);
	else if (ft_strcmp(args[0], "env") == 0)
		status = _env_(envs);
	else if (ft_strcmp(args[0], "echo") == 0)
		status = _echo_(args + 1);
	else if (ft_strcmp(args[0], "pwd") == 0)
		status = _pwd_(manage_pwd(NULL));
	else if (ft_strcmp(args[0], "unset") == 0)
		_unset_(envs, args + 1);
	else if (ft_strcmp(args[0], "exit") == 0)
		_exit_(args + 1);
	else
		return (ret = not_builtin(args, envs),
			free_double_pointer((void **)args), ret);
	free_double_pointer((void **)args);
	return (status);
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
	return (execution_simple_command(tree->content, env_list));
}
