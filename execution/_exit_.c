/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:27:26 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/07 17:14:50 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/minishell.h"

void	_exit_(char **args)
{
	int	i;

	i = -1;
	if (isatty(STDOUT_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);
	if (args && args[0])
	{
		while (args[0][++i])
			if (!ft_isdigit(args[0][i]) && ((args[0][i] == '-'
						|| args[0][i] == '+') && !ft_isdigit(args[0][i + 1])))
				break ;
		if (args[0][i])
		{
			print_error("bash: exit: ", args[0], ": numiric argument required");
			exit(255);
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
