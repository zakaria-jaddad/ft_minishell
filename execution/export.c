/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:20:51 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/17 08:02:10 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_export(t_list **list, char **args, int append)
{
	t_env	*env;
	char	*tmp;

	env = get_env(*list, args[0]);
	if (append && env)
	{
		tmp = ft_strjoin(env->value, args[1] + 1);
		free(args[1]);
		args[1] = tmp;
	}
	if (env && (!args[1] || !ft_strcmp(args[1], "")))
		return ;
	if (env && append)
		edit_env(env, args[1]);
	else if (env)
		edit_env(env, args[1] + 1);
	else
	{
		if (args[1] && args[1][0] && args[1][1])
			append_env(list, args[0], args[1] + 1);
		else if (args[1] && args[1][0] == '=')
			append_env(list, args[0], "\0");
		else
			append_env(list, args[0], NULL);
	}
}

int	find_first_arg(char *arg, int *append_)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (arg[i] == '=')
			break ;
	if (!i)
		return (-1);
	if (arg[i - 1] == '+' && arg[i] == '=')
	{
		(*append_)++;
		i--;
	}
	return (i);
}

int	check_append_norms(int i, char *arg)
{
	int	j;

	j = i;
	while (j > 0 && arg[j] == '+')
		j--;
	return (j);
}

int	split_by_first_equal(char *arg, t_list **list)
{
	char	**rv;
	int		i;
	int		append_;

	append_ = 0;
	i = find_first_arg(arg, &append_);
	if (i == -1)
		return (0);
	if (arg[check_append_norms(i, arg)] == '+')
		return (0);
	rv = malloc(sizeof(char *) * (2 + 1));
	if (rv == NULL)
		return (0);
	rv[0] = ft_substr(arg, 0, i);
	if (rv[0] == NULL)
		return (0);
	if (append_)
		i++;
	rv[1] = ft_substr(arg, i, ft_strlen(arg));
	if (rv[1] == NULL)
		return (free(rv[0]), 0);
	rv[2] = NULL;
	add_export(list, rv, append_);
	free_double_pointer((void **)rv);
	return (1);
}

int	_export_(t_list **list, char **args)
{
	int	i;
	int	status;

	if (!list)
		return (-1);
	if (!args || !args[0])
		return (print_envs("declare -x ", sort_envs(*list)));
	i = 0;
	status = 0;
	while (args[i])
	{
		if (!check_arg(args[i]))
		{
			status = (ft_fprintf_putstr_fd(2,
						"minishell: export: not a valid identifier\n"), 1);
			i++;
			continue ;
		}
		if (split_by_first_equal(args[i], list) == 0)
			status = (ft_fprintf_putstr_fd(2,
						"minishell: export: not a valid identifier\n"), 1);
		i++;
	}
	return (status_x(status, 1));
}
