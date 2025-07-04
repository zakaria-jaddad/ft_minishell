/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:11:14 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/01 17:11:14 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

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

int	join_the_str(char **res, int i, t_env **rv_env)
{
	char	*str;
	t_env	*env;

	env = *rv_env;
	str = ft_strjoin(env->key, "=");
	if (env->value)
		res[i] = ft_strjoin(str, env->value);
	if (!res[i] || !str)
		return (free_double_pointer((void **)res), free(str), 0);
	free(str);
	*rv_env = env;
	return (1);
}

char	**envs_list_to_double_pointer(t_list *env_list)
{
	int		i;
	char	**res;
	t_env	*env;

	i = 0;
	if (!env_list)
		return (NULL);
	res = malloc(sizeof(char *) * (count_envs(env_list) + 1));
	if (!res)
		return (NULL);
	while (env_list)
	{
		env = env_list->content;
		if (env && env->value && ft_strcmp(env->value, ""))
			if (!join_the_str(res, i++, &env))
				return (NULL);
		env_list = env_list->next;
	}
	return (res[i] = NULL, res);
}
