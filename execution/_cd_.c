/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:28:41 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/21 11:27:39 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	add_pwd_manual(char *path)
{
	int		length;
	char	*joined;

	ft_fprintf_putstr_fd(STDERR_FILENO,
		"cd: error retrieving current directory: getcwd: cannot access parent "
		"directories: No such file or directory\n");
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

void	escape_double_point(char **new_path)
{
	char	*tmp;
	int		j;

	j = ft_strlen(*new_path);
	while (j > 0 && (*new_path)[j] != '/')
		j--;
	tmp = *new_path;
	*new_path = ft_substr(tmp, 0, j);
	free(tmp);
}

void	reform_path(char **path)
{
	char	**dirs;
	int		i;
	char	*new_path;

	dirs = ft_split(*path, '/');
	new_path = ft_strdup(manage_pwd(NULL));
	i = -1;
	while (dirs[++i])
	{
		if (!ft_strcmp(dirs[i], "."))
			continue ;
		else if (!ft_strcmp(dirs[i], ".."))
			escape_double_point(&new_path);
		else
			join_paths(&new_path, dirs[i]);
		if (access(new_path, F_OK) < 0)
			return (free(new_path), free_double_pointer((void **)dirs));
	}
	if (dirs[0] && ft_strcmp(dirs[0], ""))
	{
		free(*path);
		*path = ft_strdup(new_path);
	}
	free(new_path);
	free_double_pointer((void **)dirs);
}

int	cd_helper(char *path, t_list *list)
{
	char	*cwd;

	if (!path || ft_strcmp(path, "") == 0)
		return (free(path), 1);
	reform_path(&path);
	if (chdir(path) < 0)
	{
		display_execve_error(path, 1);
		return (free(path), 1);
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
	free(path);
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
			ft_fprintf_putstr_fd(STDERR_FILENO, "bash: cd: HOME not set\n");
			return (1);
		}
		if (cd_helper(ft_strdup((char *)env->value), envs))
			return (1);
	}
	else if (cd_helper(ft_strdup(args[0]), envs))
		return (1);
	return (0);
}
