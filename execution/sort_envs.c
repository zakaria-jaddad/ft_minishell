/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:36:15 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/15 09:59:37 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

t_list	*sort_envs(t_list *list)
{
	void	*content;
	t_list	*tmp;

	if (!list)
		return (NULL);
	while (list->next && list->content)
	{
		tmp = list->next;
		while (tmp && tmp->content)
		{
			if (ft_strcmp(((t_env *)list->content)->key,
					((t_env *)tmp->content)->key) > 0)
			{
				content = list->content;
				list->content = tmp->content;
				tmp->content = content;
			}
			tmp = tmp->next;
		}
		list = list->next;
	}
	while (list && list->prev)
		list = list->prev;
	return (list);
}
