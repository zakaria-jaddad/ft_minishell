/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:34 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/06 08:16:40 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

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
		p[i] = NULL;
		i++;
	}
	free(p);
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

void	join_paths(char **path, char *toadd)
{
	char	*tmp;

	tmp = ft_strjoin(*path, "/");
	free(*path);
	*path = ft_strjoin(tmp, toadd);
	free(tmp);
}
