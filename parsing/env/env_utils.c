/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:11:58 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/09 19:41:09 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	free_env(void *env)
{
	if (env == NULL)
		return ;
	((t_env *)env)->key = (free(((t_env *)env)->key), NULL);
	((t_env *)env)->value = (free(((t_env *)env)->value), NULL);
	free(env);
}

t_env	*get_env(t_list *env_lst, char *key)
{
	t_env	*env;

	if (env_lst == NULL)
		return (NULL);
	while (env_lst)
	{
		env = (t_env *)env_lst->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			return (env);
		}
		env_lst = env_lst->next;
	}
	return (NULL);
}

t_env	*edit_env(t_env *env, char *new_value)
{
	free(env->value);
	env->value = ft_strdup(new_value);
	if (env->value == NULL)
		return (NULL);
	return (env);
}

t_list	*append_env(t_list **env_lst, char *key, char *value)
{
	t_env	*env_content;
	t_list	*env_node;

	env_content = (t_env *)malloc(sizeof(t_env));
	if (env_content == NULL)
		return (NULL);
	env_content->key = ft_strdup(key);
	if (env_content->key == NULL)
		return (NULL);
	env_content->value = ft_strdup(value);
	if (env_content->value == NULL)
		return (free(env_content->key), NULL);
	env_node = ft_lstnew(env_content);
	if (env_node == NULL)
		return (free(env_content), free_env(env_content), NULL);
	ft_lstadd_back(env_lst, env_node);
	return (*env_lst);
}
