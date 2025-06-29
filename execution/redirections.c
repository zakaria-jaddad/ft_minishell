#include "../includes/execution.h"
#include "../includes/minishell.h"

void	get_last_redir_fd(t_cmd *t, int *out, int *in, t_list *envs)
{
	int	fd;

	fd = -1;
	if (!t)
		return ;
	if (NODE_OUT_REDIR == t->type || t->type == NODE_APPEND_REDIR) // > or >>
	{
		*out = found_file(t, t->type, envs);
		if (*out == -1)
			return ;
	}
	else if (NODE_IN_REDIR == t->type || NODE_HEREDOC == t->type) // < or <<
	{
		*in = found_file(t, t->type, envs);
		if (*in == -1)
			return ;
	}
	if (t->right)
		get_last_redir_fd(t->right, out, in, envs);
}

int	run_redir(t_cmd *t, t_list *envs)
{
	int		status;
	int		out_fd;
	int		in_fd;
	pid_t	pid;

	status = 0;
	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	get_last_redir_fd(t, &out_fd, &in_fd, envs);
	if (in_fd == -1 || out_fd == -1)
		return (status_x(1, 1));
	pid = fork();
	if (0 == pid)
	{
		if (signal(SIGINT, handle_ctrC_fork) == SIG_ERR)
			ft_fprintf(STDERR_FILENO, "signal: error handling ctr+c!!\n");
		if (in_fd)
			dup2(in_fd, STDIN_FILENO);
		if (out_fd)
			dup2(out_fd, STDOUT_FILENO);
		status = execution(t->left, envs);
		if (t->type == NODE_OUT_REDIR || t->type == NODE_APPEND_REDIR)
			close(out_fd);
		if (t->type == NODE_IN_REDIR || t->type == NODE_HEREDOC)
			close(in_fd);
		exit(status);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (t->type == NODE_OUT_REDIR || t->type == NODE_APPEND_REDIR)
			close(out_fd);
		if (t->type == NODE_IN_REDIR || t->type == NODE_HEREDOC)
			close(in_fd);
	}
	else
		return (ft_fprintf(2, "fork error!\n"), 1);
	return (status_x(status, 0));
}

int	run_in_pipe(t_cmd *t, t_list *envs)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;
	int		fd[2];

	if (pipe(fd) < 0)
		return (ft_fprintf(2, "pipe: error!\n"), 1);
	status = 0;
	pid_left = fork();
	if (pid_left < 0)
		return (close(fd[0]), close(fd[1]), ft_fprintf(2, "fork: error!!\n"),
			1);
	if (pid_left == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		status = execution(t->left, envs);
		exit(status);
	}
	pid_right = fork();
	if (pid_right < 0)
		return (close(fd[0]), close(fd[1]), waitpid(pid_left, 0, 0),
			ft_fprintf(2, "fork: error!!\n"), 1);
	if (pid_right == 0)
	{
		if (signal(SIGINT, handle_ctrC_fork) == SIG_ERR)
			ft_fprintf(STDERR_FILENO, "signal: error handling ctr+c!!\n");
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		status = execution(t->right, envs);
		exit(status);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
	return (status_x(status, 0));
}
