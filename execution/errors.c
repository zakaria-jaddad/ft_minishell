/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:40:40 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/24 05:03:20 by mouait-e         ###   ########.fr       */
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
	if (!*cmd)
		return (cmd);
	paths = ft_split(path, ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		rv = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(rv, X_OK))
			break ;
		free(rv);
		rv = NULL;
		i++;
	}
	free_double_pointer((void **)paths);
	if (rv)
		return (rv);
	return (ft_strdup(cmd));
}

int	display_execve_error(char *command, int builtin)
{
	if (errno == ENOENT)
	{
		if (ft_strnstr(command, "/", ft_strlen(command)) || builtin)
			ft_fprintf(2, "%s", "minishell: No such file or directory\n");
		else
			ft_fprintf_putstr_fd(2, "minishell: Command not found\n");
		return (127);
	}
	else if (errno == EACCES)
		return (ft_fprintf_putstr_fd(2, "minishell: Permission denied\n"), 126);
	else if (errno == EISDIR)
		return (ft_fprintf_putstr_fd(2, "minishell: Is a directory\n"), 126);
	else if (errno == ENOTDIR)
		return (ft_fprintf_putstr_fd(2, "minishell: Not a directory\n"), 126);
	else
		ft_fprintf_putstr_fd(2, strerror(errno));
	return (errno);
}
