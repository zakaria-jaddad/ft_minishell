#include "../includes/minishell.h"

void	clear_env(t_env *env)
{
	env->key = (free(env->key), NULL);
	env->value = (free(env->value), NULL);
}

void	clear_envs(t_list **env)
{
	t_list	*head;

	head = *env;
	while (*env)
	{
		clear_env((t_env *)(*env)->content);
		*env = (*env)->next;
	}
	ft_lstclear(&head, free);
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
		return (free(env_content), clear_env(env_content), NULL);
	ft_lstadd_back(env_lst, env_node);
	return (*env_lst);
}
