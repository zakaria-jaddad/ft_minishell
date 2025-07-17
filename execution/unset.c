/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:16:48 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/17 03:47:54 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_arg(char *args)
{
	int	j;

	if (((args[0] >= '0' && args[0] <= '9') || args[0] == '='))
		return (0);
	j = -1;
	while (args[++j] && args[j] != '=')
		if (!(args[j] >= 'a' && args[j] <= 'z') && !(args[j] >= 'A'
				&& args[j] <= 'Z') && !(args[j] >= '0' && args[j] <= '9'
				&& j > 0) && !(args[j] == '+' && args[j + 1] == '=')
			&& args[j] != '_')
			return (0);
	return (1);
}

int	check_arg_unset(char *args)
{
	int	j;

	if (((args[0] >= '0' && args[0] <= '9') || args[0] == '='))
		return (0);
	j = -1;
	while (args[++j])
		if (!(args[j] >= 'a' && args[j] <= 'z') && !(args[j] >= 'A'
				&& args[j] <= 'Z') && !(args[j] >= '0' && args[j] <= '9'
				&& j > 0) && !(args[j] == '+' && args[j + 1] == '=')
			&& args[j] != '_')
			return (0);
	return (1);
}

int	_unset_(t_list **envs, char **args)
{
	t_list	*var;
	int		i;
	int		status;

	status = 0;
	i = 0;
	while (args[i])
	{
		if (!args[i][0] || !check_arg_unset(args[i]))
		{
			status = (ft_fprintf_putstr_fd(2,
						"bash: unset: not a valid identifier\n"), 1);
			i++;
			continue ;
		}
		var = find_node(*envs, args[i]);
		if (var)
			ft_lst_rm_one(envs, var, free_env);
		i++;
	}
	return (status);
}
