/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:41:29 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/14 06:43:25 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_fork(t_cmd *t, int out_fd, int in_fd, t_list *envs)
{
	int	status;

	status = 0;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		ft_fprintf(STDERR_FILENO, "signal: error handling ctr+c!!\n");
	if (in_fd)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd)
		dup2(out_fd, STDOUT_FILENO);
	if (t->left)
		status = execution(t->left, envs);
	if (t->type == NODE_OUT_REDIR || t->type == NODE_APPEND_REDIR)
		close(out_fd);
	if (t->type == NODE_IN_REDIR || t->type == NODE_HEREDOC)
		close(in_fd);
	exit(status);
}

void	wait_for_redir(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status))
		status_x((unsigned char)(127 + status), 1);
	else if (WIFSIGNALED(status))
		status_x((unsigned char)(128 + status), 1);
	else
		status_x(0, 1);
}

int	run_redir(t_cmd *t, t_list *envs)
{
	int		out_fd;
	int		in_fd;
	pid_t	pid;

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	get_last_redir_fd(t, &out_fd, &in_fd, envs);
	if (in_fd == -1 || out_fd == -1)
		return (status_x(1, 1));
	pid = fork();
	if (0 == pid)
		redir_fork(t, out_fd, in_fd, envs);
	else if (pid > 0)
	{
		wait_for_redir(pid);
		if (t->type == NODE_OUT_REDIR || t->type == NODE_APPEND_REDIR)
			close(out_fd);
		if (t->type == NODE_IN_REDIR || t->type == NODE_HEREDOC)
			close(in_fd);
	}
	else
		return (ft_fprintf(2, "fork error!\n"), 1);
	return (status_x(0, 0));
}

void	pipe_fork(int *fd, int fd_to_dup, t_cmd *t, t_list *envs)
{
	int	status;

	if (fd_to_dup == STDOUT_FILENO)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (fd_to_dup == STDIN_FILENO)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	status = execution(t, envs);
	exit(status);
}

int	run_in_pipe(t_cmd *t, t_list *envs)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;
	int		fd[2];

	if (pipe(fd) < 0)
		return (ft_fprintf(2, "pipe: error!\n"), 1);
	in_pipe(1, 1);
	pid_left = fork();
	if (pid_left < 0)
		return (close(fd[0]), close(fd[1]), ft_fprintf(2, "fork:err!\n"), 1);
	if (pid_left == 0)
		pipe_fork(fd, STDOUT_FILENO, t->left, envs);
	pid_right = fork();
	if (pid_right < 0)
		return (close(fd[0]), close(fd[1]), waitpid(pid_left, 0, 0),
			ft_fprintf(2, "fork: error!!\n"), 1);
	if (pid_right == 0)
		pipe_fork(fd, STDIN_FILENO, t->right, envs);
	in_pipe(0, 1);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	return (status_x(WEXITSTATUS(status), 1));
}
