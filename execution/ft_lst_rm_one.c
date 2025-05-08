/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_rm_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 01:05:21 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/08 02:13:59 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	ft_lst_rm_one(t_list *nodeToDel, void clear_content(t_env *content))
{
	t_list	*prev;
	t_list	*next;

	clear_content(nodeToDel->content);
	prev = nodeToDel->prev;
	next = nodeToDel->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(nodeToDel);
}
