/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:41:29 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/15 01:00:25 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_last_redir_fd(t_cmd *t, int *out, int *in, t_list *envs);

int	keep_going(t_cmd *t, int *in, int *out, t_list *envs)
{
	int	in_fd;
	int	out_fd;
	int	fd;

	in_fd = *in;
	out_fd = *out;
	fd = get_last_redir_fd(t, out, in, envs);
	close(in_fd);
	close(out_fd);
	return (fd);
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
		fd = keep_going(t->right, in, out, envs);
	return (fd);
}
