/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:27:26 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/11 00:38:06 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/minishell.h"

int in_pipe(int val, int modify)
{
	static int i;

	if (modify)
		i = val;	
	return (i);
}

void	_exit_(char **args)
{
	int	i;

	i = -1;
	if (!in_pipe(0,0))
		write(STDOUT_FILENO, "exit\n", 5);
	if (args && args[0])
	{
		if (args[0][0] == '-' || args[0][0] == '+')
			i++;
		while (args[0][++i])
			if (!ft_isdigit(args[0][i]))
				break ;
		if (args[0][i])
		{
			print_error("bash: exit: ", args[0], ": numiric argument required");
			exit(255);
		}
		if (args[1])
		{
			print_error("bash: exit: ", NULL, "too many arguments");
			status_x(1,1);
			return ;
		}
		exit((unsigned char)ft_atoi(args[0]));
	}
	exit(status_x(0, 0));
}
