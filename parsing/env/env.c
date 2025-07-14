/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:05:52 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/14 20:32:51 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/env.h"
#include <stdlib.h>

static int	locate_first_equale(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	**get_split_env(char *env)
{
	char	**_env;
	int		equal_pos;

	if (env == NULL)
		return (NULL);
	_env = (char **)malloc(sizeof(char *) * 3);
	if (_env == NULL)
		return (NULL);
	ft_bzero(_env, sizeof(_env));
	equal_pos = locate_first_equale(env);
	if (equal_pos == -1)
		return (NULL);
	_env[0] = ft_substr(env, 0, equal_pos);
	if (_env[0] == NULL)
		return (free(_env), _env = NULL, NULL);
	if (ft_strcmp(_env[0], "_") == 0)
		return (free(_env[0]), _env[0] = NULL, free(_env), _env = NULL, NULL);
	_env[1] = ft_substr(env, equal_pos + 1, ft_strlen(env) - equal_pos + 1);
	if (_env[1] == NULL)
		return (free(_env[0]), _env[0] = NULL, free(_env), _env = NULL, NULL);
	return (_env);
}

static t_list	*simple_env(t_list *env_lst)
{
	char	path_buff[PATH_MAX];

	if (getcwd(path_buff, PATH_MAX) == NULL)
		return (NULL);
	if (append_env(&env_lst, "PWD", path_buff) == NULL)
		return (NULL);
	if (append_env(&env_lst, "SHLVL", "1") == NULL)
		return (ft_lstclear(&env_lst, free_env), NULL);
	if (append_env(&env_lst, "OLDPWD", NULL) == NULL)
		return (ft_lstclear(&env_lst, free_env), NULL);
	if (append_env(&env_lst, "PATH",
			"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.") == NULL)
		return (ft_lstclear(&env_lst, free_env), NULL);
	return (env_lst);
}

t_list	*envs_init(char **env, ...)
{
	t_list	*env_lst;
	t_list	*node;
	char	**se;
	t_env	*ec;

	env_lst = NULL;
	if (*env == NULL)
		return (simple_env(env_lst));
	while (*env)
	{
		se = get_split_env(*env);
		if (se != NULL)
		{
			ec = (t_env *)malloc(sizeof(t_env));
			if (ec == NULL)
				return (ft_lstclear(&env_lst, free_env), NULL);
			(void)!(ec->key = se[0], ec->value = se[1], free(se), 0);
			node = ft_lstnew(ec);
			if (node == NULL)
				return (ft_lstclear(&env_lst, free_env), NULL);
			(ft_lstadd_back(&env_lst, node));
		}
		env++;
	}
	return (env_lst);
}
