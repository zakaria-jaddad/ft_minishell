/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_rm_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 01:05:21 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/21 23:08:57 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_rm_one(t_list *node_to_del, void clear_content(void *content))
{
	t_list	*prev;
	t_list	*next;

	if (!node_to_del)
		return ;
	if (node_to_del->content)
		clear_content(node_to_del->content);
	prev = node_to_del->prev;
	next = node_to_del->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(node_to_del);
}
