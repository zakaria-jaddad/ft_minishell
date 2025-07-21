/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:41:29 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/21 02:28:45 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

int	redir_fork(t_cmd *t, int out_fd, int in_fd, t_list *envs)
{
	int	status;

	status = 0;
	if (in_fd > 2)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd > 2)
		dup2(out_fd, STDOUT_FILENO);
	if (t->left)
		status = execution(t->left, &envs);
	return (status);
}

int	run_redir(t_cmd *t, t_list *envs)
{
	int	out_fd;
	int	in_fd;
	int	out;
	int	in;
	int	status;

	status = 0;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	get_last_redir_fd(t, &out_fd, &in_fd, envs);
	if (in_fd == -1 || out_fd == -1)
		return (fd_cleaner(), status_x(1, 1));
	status = redir_fork(t, out_fd, in_fd, envs);
	dup2(in, 0);
	dup2(out, 1);
	fd_cleaner();
	return (status_x(status, 1));
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
	status = execution(t, &envs);
	exit(status);
}

int	run_in_pipe(t_cmd *t, t_list *envs)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;
	int		fd[2];

	status = 0;
	if (pipe(fd) < 0)
		return (ft_fprintf_putstr_fd(2, "pipe: error!\n"), 1);
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
	fd_cleaner();
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	return (status_x(WEXITSTATUS(status), 1));
}
