/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:26:10 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/04 12:26:40 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	_echo_(char **args, int fd)
{
	int	i;
	int	j;

	i = 0;
	if (!args || !*args)
	{
		write(fd, "\n", 1);
		return (-1);
	}
	if (ft_strncmp(args[0], "-n", ft_strlen(args[0])) == 0)
		i++;
	while (args[i])
	{
		j = 0;
		while (args[i][j] != '\0')
			write(fd, &args[i][j++], 1);
		if (args[++i])
			write(fd, " ", 1);
	}
	if (ft_strncmp(args[0], "-n", ft_strlen(args[0])) != 0 || !args[0])
		write(1, "\n", 1);
	return (0);
}
