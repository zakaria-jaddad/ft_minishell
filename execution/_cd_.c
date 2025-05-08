/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:28:41 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/06 15:41:22 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include <unistd.h>

int	cd_helper(char *path, t_list *list)
{
	if (chdir(path) < 0)
	{
		ft_fprintf(2, "shell_imzin: cd: %s: No such file or directory\n", path);
		return (-1);
	}
	edit_env(get_env(list, "OLDPWD"), get_env(list, "OLDPWD")->value);
	edit_env(get_env(list, "PWD"), getcwd(NULL, 0));
	return (0);
}

int	_cd_(t_list *list, char **args)
{
	t_env	*env;

	if (!args || !*args)
	{
		env = get_env(list, "HOME");
		if (!env || !env->value)
			return (-1);
		if (cd_helper((char *)env->value, list))
			return (-1);
	}
	else if (args[1])
	{
		ft_fprintf(STDERR_FILENO, "cd: string not in pwd: %s\n", args[0]);
		return (-1);
	}
	else if (cd_helper(args[0], list))
		return (-1);
	return (0);
}
