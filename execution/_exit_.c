/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:27:26 by mouait-e          #+#    #+#             */
/*   Updated: 2025/06/29 21:36:35 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/minishell.h"

void	_exit_(char **args)
{
	int	i;

	i = -1;
	write(1, "exit\n", 5);
	if (args && args[0])
	{
		while (args[0][++i])
		{
			if (!ft_isdigit(args[0][i]) && ((args[0][i] == '-'
						|| args[0][i] == '+') && !ft_isdigit(args[0][i + 1])))
				break ;
		}
		if (args[0][i])
		{
			print_error("bash: exit: ", args[0], ": numiric argument required");
			exit(2);
		}
		if (args[1])
		{
			print_error("bash: exit: ", NULL, "too many arguments");
			return ;
		}
		exit((unsigned char)ft_atoi(args[0]));
	}
	exit(status_x(0, 0));
}
