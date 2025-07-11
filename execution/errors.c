/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:40:40 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/11 03:43:35 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			ft_fprintf(2, "minishell: %s: No such file or directory\n",
				command);
		else
			ft_fprintf(2, "minishell: %s: Command not found\n", command);
	}
	else if (errno == EISDIR)
		ft_fprintf(2, "minishell: %s: Is a directory\n", command);
	else if (errno == ENOEXEC)
		ft_fprintf(2, "minishell: %s: Exec format error\n", command);
	else if (errno == ENOMEM)
		ft_fprintf(2, "minishell: %s: Cannot allocate memory\n", command);
	else if (errno == EFAULT)
		ft_fprintf(2, "minishell: %s: Bad address\n", command);
	else if (errno == ENOTDIR)
		ft_fprintf(2, "minishell: %s: Not a directory\n", command);
	else
		ft_fprintf(2, "minishell: %s: %s\n", command, strerror(errno));
	return (errno);
}
