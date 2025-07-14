/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:26:10 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/14 08:42:13 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include <stdlib.h>
#include <unistd.h>

void	handle_args(int *i, int *nl, char **args)
{
	int	j;

	while (args[*i])
	{
		j = 0;
		if (args[*i][j++] == '-')
			while (args[*i][j] == 'n')
				j++;
		if (!args[*i][j] && j > 1)
			*nl += 1;
		else
			break ;
		*i += 1;
	}
}

int	_echo_(char **args)
{
	int		i;
	int		nl;
	char	*str;

	nl = 0;
	str = NULL;
	if (!args)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	i = 0;
	handle_args(&i, &nl, args);
	while (args[i])
	{
		if (args[i])
			append_str(&str, args[i]);
		if (args[++i])
			append_str(&str, " ");
	}
	if (!nl || !args[0])
		append_str(&str, "\n");
	ft_fprintf_putstr_fd(STDOUT_FILENO, str);
	str = (free(str), NULL);
	return (0);
}
