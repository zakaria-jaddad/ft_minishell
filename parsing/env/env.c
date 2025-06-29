/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:05:52 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/29 21:52:39 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/env.h"

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
	if (append_env(&env_lst, "_", "/usr/bin/env") == NULL)
		return (ft_lstclear(&env_lst, free_env), NULL);
	if (append_env(&env_lst, "PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:. ") == NULL)
		return (ft_lstclear(&env_lst, free_env), NULL);
	return (env_lst);
}

t_list	*envs_init(char **env, ...)
{
	t_list	*env_lst;
	t_list	*node;
	char	**split_env;
	t_env	*env_content;

	env_lst = NULL;
	if (*env == NULL)
		return (simple_env(env_lst));
	while (*env)
	{
		split_env = get_split_env(*env);
		if (split_env == NULL)
			return (ft_lstclear(&env_lst, free_env), NULL);
		env_content = (t_env *)malloc(sizeof(t_env));
		if (env_content == NULL)
			return (ft_lstclear(&env_lst, free_env), NULL);
		env_content->key = split_env[0];
		env_content->value = split_env[1];
		free(split_env);
		node = ft_lstnew(env_content);
		if (node == NULL)
			return (ft_lstclear(&env_lst, free_env), NULL);
		(ft_lstadd_back(&env_lst, node), env++);
	}
	return (env_lst);
}
