/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:26:10 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/23 12:15:01 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	_echo_(t_list *args, int fd)
{
	t_list	*s;

	if (!args || !args->content)
	{
		write(fd, "\n", 1);
		return (1);
	}
	s = args;
	if (ft_strncmp(args->content, "-n", ft_strlen(args->content)) == 0)
		args = args->next;
	while (args)
	{
		if (args->content)
			ft_fprintf(fd, "%s", args->content);
		args = args->next;
	}
	if (ft_strncmp(s->content, "-n", ft_strlen(s->content)) != 0 || !s->content)
		ft_fprintf(fd, "\n");
	ft_lstclear(&s, free);
	return (0);
}
