/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:41:29 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/15 12:19:30 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_last_redir_fd(t_cmd *t, int *out, int *in, t_list *envs);

void	fd_cleaner(void)
{
	int	i;

	i = 3;
	while (i <= FD_SETSIZE)
		close(i++);
}

int	get_last_redir_fd(t_cmd *t, int *out, int *in, t_list *envs)
{
	int	fd;

	if (!t)
		return (0);
	fd = 0;
	if (NODE_OUT_REDIR == t->type || t->type == NODE_APPEND_REDIR)
	{
		if (*out > 2)
			close(*out);
		*out = found_file(t, t->type, envs);
		if (*out == -1)
			return (-1);
	}
	else if (NODE_IN_REDIR == t->type || NODE_HEREDOC == t->type)
	{
		if (*in > 2)
			close(*in);
		*in = found_file(t, t->type, envs);
		if (*in == -1)
			return (-1);
	}
	if (t->right)
		fd = get_last_redir_fd(t->right, out, in, envs);
	return (fd);
}
