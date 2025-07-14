/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:27:26 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/14 15:48:45 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/minishell.h"

int	in_pipe(int val, int modify)
{
	static int	i;

	if (modify)
		i = val;
	return (i);
}

void	_exit_escaping_norms(char *str)
{
	if (ft_atoi(str) == ATOIERROR)
	{
		print_error("minishell: exit: ", str, ": numiric argument required");
		exit(255);
	}
	exit((unsigned char)ft_atoi(str));
}

void	_exit_(char **args)
{
	int	i;

	i = 0;
	if (!in_pipe(0, 0))
		write(STDOUT_FILENO, "exit\n", 5);
	if (args && args[0])
	{
		if (args[0][i] == '-' || args[0][i] == '+')
			if (args[0][++i] == 0)
				(void)(print_error("minishell: exit: ", args[0],
						": numiric argument required"), exit(255));
		while (args[0][i] && ft_isdigit(args[0][i]))
			i++;
		if (args[0][i])
			(void)(print_error("minishell: exit: ", args[0],
					": numiric argument required"), exit(255));
		if (args[1])
			return ((void)(print_error("minishell: exit: ", NULL,
					"too many arguments"), status_x(1, 1)));
	}
	exit(status_x(0, 0));
}
