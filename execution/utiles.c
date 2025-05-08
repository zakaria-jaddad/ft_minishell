/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:34 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/08 01:27:26 by mouait-e         ###   ########.fr       */
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
	t_env	*env;
	int		count;

	if (!envs)
		return (0);
	while (envs)
	{
		env = envs->content;
		if (env && env->key)
			count++;
		envs = envs->next;
	}
	return (count);
}

char	**list_to_double_pointer(t_list *env_list)
{
	int		i;
	char	**res;
	t_env	*env;
	char	*str;

	i = 0;
	res = malloc(sizeof(char *) * (count_envs(env_list) + 1));
	if (!res)
		return (NULL);
	while (env_list)
	{
		env = env_list->content;
		if (env && env->key && env->value)
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
