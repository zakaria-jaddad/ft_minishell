/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:16:48 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/07 17:16:48 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	_unset_(t_list *envs, char **args)
{
	t_list	*var;
	int		i;

	i = 0;
	while (args[i])
	{
		var = find_node(envs, args[i]);
		if (var)
			ft_lst_rm_one(&envs, var, free_env);
		i++;
	}
}
