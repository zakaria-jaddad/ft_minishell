/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:32:47 by mouait-e          #+#    #+#             */
/*   Updated: 2025/06/23 12:45:02 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void _unset_(t_list *envs, char **args) {
  t_list *var;
  int i;

	i = 0;
	while (args[i])
	{
		var = find_node(envs, args[i]);
		if (var)
			ft_lst_rm_one(&envs, var, free_env);
		i++;
	}
}

int	print_envs(char *declare, t_list *list)
{
	t_env	*env;

	while (list)
	{
		env = list->content;
		if (!declare)
		{
			if (env->value)
				printf("%s=\"%s\"\n", env->key, env->value);
		}
		else
			printf("%s%s=\"%s\"\n", declare, env->key, env->value);
		list = list->next;
	}
	return (0);
}

int _env_(t_list *list) {
  if (!list)
    return (-1);
  return (print_envs(NULL, list));
}

/* static void	swap_two_envs(t_list *env1, t_list *env2) */
/* { */
/* 	t_env	*tmp; */
/**/
/* 	tmp = env1->content; */
/* 	env1->content = env2->content; */
/* 	env2->content = tmp; */
/* } */

void add_export(t_list *list, char **args) {
  t_env *env;

  env = get_env(list, args[0]);
  if (env)
    edit_env(env, args[1]);
  else {
    if (args[1])
      append_env(&list, args[0], args[1]);
    else
      append_env(&list, args[0], "\0");
  }
}

int _export_(t_list *list, char **args) {
  int i;

  if (!list)
    return (-1);
  if (!args || !args[0])
    return (print_envs("declare -x ", list));
  i = 0;
  while (args[i]) {
    add_export(list, ft_split(args[i], '='));
    i++;
  }
  return (0);
}
