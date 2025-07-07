/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:20:51 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/07 20:56:15 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_export(t_list *list, char **args, int append)
{
	t_env	*env;

	env = get_env(list, args[0]);
	if (append && env)
		args[1] = ft_strjoin(env->value, args[1] + 1);
	if (env && (!args[1] || !ft_strcmp(args[1], "")))
		return ;
	if (env && append)
		edit_env(env, args[1]);
	else if (env)
		edit_env(env, args[1] + 1);
	else
	{
		if (args[1] && args[1][0] && args[1][1])
			append_env(&list, args[0], args[1] + 1);
		else if (args[1] && args[1][0] == '=')
			append_env(&list, args[0], "\0");
		else
			append_env(&list, args[0], NULL);
	}
}

int	check_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		if (((args[i][0] >= '0' && args[i][0] <= '9') || args[i][0] == '='))
			return (ft_fprintf(2,
					"minishell: export: `%s`: not a valid identifier\n",
					args[i]), 0);
		j = -1;
		while (args[i][++j] && args[i][j] != '=')
			if (!(args[i][j] >= 'a' && args[i][j] <= 'z') && !(args[i][j] >= 'A'
					&& args[i][j] <= 'Z') && !(args[i][j] >= '0'
					&& args[i][j] <= '9' && j > 0) && !(args[i][j] == '+'
					&& args[i][j + 1] == '='))
				return (ft_fprintf(2,
						"minishell: export: `%s`: not a valid identifier\n",
						args[i]), 0);
		i++;
	}
	return (1);
}

char	**split_by_first_equal(char *arg, t_list *list)
{
	char	**rv;
	int		i;
	int		append_;

	i = -1;
	append_ = 0;
	while (arg[++i])
		if (arg[i] == '=')
			break ;
	if (!i)
		return (NULL);
	if (arg[i - 1] == '+' && arg[i] == '=')
	{
		append_++;
		i--;
	}
	rv = malloc(sizeof(char *) * (2 + 1));
	rv[0] = ft_substr(arg, 0, i);
	if (append_)
		i++;
	rv[1] = ft_substr(arg, i, ft_strlen(arg));
	rv[2] = NULL;
	add_export(list, rv, append_);
	ft_split_free(rv);
	return (NOTNULL);
}

int	_export_(t_list *list, char **args)
{
	int	i;

	if (!list)
		return (-1);
	if (!args || !args[0])
		return (print_envs("declare -x ", list));
	i = 0;
	if (!check_args(args))
		return (status_x(1, 1));
	while (args[i])
	{
		split_by_first_equal(args[i], list);
		i++;
	}
	return (0);
}
