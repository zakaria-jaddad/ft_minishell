/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:32:47 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/08 18:58:32 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_envs(char *declare, t_list *list)
{
	t_env	*env;

	while (list)
	{
		env = list->content;
		if (!declare)
		{
			if (env->value && ft_strcmp(env->value, ""))
				printf("%s=%s\n", env->key, env->value);
		}
		else if (env->value)
			printf("%s%s=\"%s\"\n", declare, env->key, env->value);
		else
			printf("%s%s\n", declare, env->key);
		list = list->next;
	}
	return (0);
}

int	_env_(t_list *list, char **args)
{
	if (!list)
		return (-1);
	if (!args || !args[0])
	{
		ft_fprintf(STDERR_FILENO, "minishell: env: nor arguments required!\n");
		return (1);
	}
	return (print_envs(NULL, sort_envs(list)));
}
