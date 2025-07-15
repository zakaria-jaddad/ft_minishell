/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:28:41 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/06 22:10:17 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	add_pwd_manual(char *path)
{
	int		length;
	char	*joined;

	ft_fprintf(STDERR_FILENO,
		"cd: error retrieving current directory: getcwd: cannot access %s",
		"parent directories: No such file or directory\n");
	length = ft_strlen(path);
	if (path[length - 1] == '/')
		path[length - 1] = '\0';
	joined = ft_strjoin(manage_pwd(NULL), "/");
	manage_pwd(joined);
	free(joined);
	joined = ft_strjoin(manage_pwd(NULL), path);
	manage_pwd(joined);
	free(joined);
}

void	chdir_fail(char **path)
{
	int	i;

	if (!ft_strcmp(*path, ".") || !ft_strcmp(*path, "./"))
	{
		*path = manage_pwd(NULL);
		return ;
	}
	if (!ft_strcmp(*path, "..") || !ft_strcmp(*path, "../"))
		*path = ft_strdup(manage_pwd(NULL));
	i = ft_strlen(*path);
	while (i > 0 && (*path)[i] != '/')
		i--;
	*path = ft_substr(*path, 0, i);
}

int	cd_helper(char *path, t_list *list)
{
	char	*cwd;

	if (!path || ft_strcmp(path, "") == 0)
		return (1);
	chdir_fail(&path);
	if (chdir(path) < 0)
	{
		ft_fprintf(2, "shell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	if (get_env(list, "OLDPWD"))
		edit_env(get_env(list, "OLDPWD"), manage_pwd(NULL));
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		manage_pwd(cwd);
		free(cwd);
	}
	else
		add_pwd_manual(path);
	if (get_env(list, "PWD"))
		edit_env(get_env(list, "PWD"), manage_pwd(NULL));
	return (0);
}

int	_cd_(t_list *envs, char **args)
{
	t_env	*env;

	if (!args || !*args)
	{
		env = get_env(envs, "HOME");
		if (!env)
		{
			ft_fprintf(STDERR_FILENO, "bash: cd: HOME not set\n");
			return (1);
		}
		if (cd_helper((char *)env->value, envs))
			return (1);
	}
	else if (cd_helper(args[0], envs))
		return (1);
	return (0);
}
