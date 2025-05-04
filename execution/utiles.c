/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:24:34 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/04 12:25:34 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

// its not a circel struct //
t_env	*find_var(t_list *envs, char *key)
{
	t_env	*env;

	if (!envs || !key || !envs->content)
		return (NULL);
	while (envs)
	{
		env = envs->content;
		if (env && ft_strcmp(env->key, key) == 0)
			return (env);
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
