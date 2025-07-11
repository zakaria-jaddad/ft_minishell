/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:30:23 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/11 02:07:28 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include <sys/fcntl.h>

int	open_file(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		if (access(file, R_OK))
		{
			if (errno == EACCES)
				ft_fprintf(STDERR_FILENO, "minishell: %s: Permission denied\n",
					file);
			else
				ft_fprintf(2, "minishell: %s: no such file or directory\n", file);
		}
		return (-1);
	}
	return (fd);
}

int	found_file(t_cmd *t, t_node_type flag, t_list *envs)
{
	int		fd;
	char	*file;

	file = NULL;
	expand_filename(&file, ((t_cmd_redir *)t->content)->filename, envs);
	if (file == NULL)
		return (-1);
	fd = -1;
	if (flag == NODE_OUT_REDIR)
		fd = open_file(file, O_TRUNC | O_WRONLY | O_CREAT);
	else if (flag == NODE_IN_REDIR)
		fd = open_file(file, O_RDONLY);
	else if (flag == NODE_APPEND_REDIR)
		fd = open_file(file, O_APPEND | O_CREAT | O_WRONLY);
	else if (flag == NODE_HEREDOC)
	{
		fd = open_file(file, O_RDONLY);
		unlink(file);
	}
	free(file);
	if (fd == -1)
		return (-1);
	return (fd);
}
