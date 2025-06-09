/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:34 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/27 09:25:51 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

// its not a circel struct //
t_list	*find_node(t_list *envs, char *key)
{
	t_env	*env;

	if (!envs || !key || !envs->content)
		return (NULL);
	while (envs)
	{
		env = envs->content;
		if (env && ft_strcmp(env->key, key) == 0)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

void	print_error(char *err, char *value, char *message)
{
	if (err)
		write(2, err, ft_strlen(err));
	if (value)
		write(2, value, ft_strlen(value));
	if (message)
		write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	free_double_pointer(void **p)
{
	int	i;

	if (!p)
		return ;
	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

int	count_envs(t_list *envs)
{
	int	count;

	if (!envs)
		return (0);
	count = 0;
	while (envs)
	{
		if (envs->content)
			count++;
		envs = envs->next;
	}
	return (count);
}

char	**envs_list_to_double_pointer(t_list *env_list)
{
	int		i;
	char	**res;
	t_env	*env;
	char	*str;

	i = 0;
	if (!env_list)
		return (NULL);
	res = malloc(sizeof(char *) * (count_envs(env_list) + 1));
	if (!res)
		return (NULL);
	while (env_list)
	{
		env = env_list->content;
		if (env && env->key)
		{
			str = ft_strjoin(env->key, "=");
			if (env->value)
				res[i] = ft_strjoin(str, env->value);
			if (!res[i++] || !str)
				return (free_double_pointer((void **)res), free(str), NULL);
			free(str);
		}
		env_list = env_list->next;
	}
	return (res[i] = NULL, res);
}

char	**list_to_double_pointer(t_list *list)
{
	int		i;
	char	**res;

	i = 0;
	if (!list)
		return (NULL);
	res = malloc(sizeof(char *) * (count_envs(list) + 1));
	if (!res)
		return (NULL);
	while (list)
	{
		res[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	res[i] = NULL;
	return (res[i] = NULL, res);
}

char	*manage_pwd(char *value)
{
	static char	*pwd;

	if (!value)
		return (pwd);
	free(pwd);
	pwd = ft_strdup(value);
	return (pwd);
}
