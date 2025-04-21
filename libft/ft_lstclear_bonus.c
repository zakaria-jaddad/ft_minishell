/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:49:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/04/21 16:04:36 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*t;
	t_list	*p;

	if (lst == NULL || del == NULL)
		return ;
	t = *lst;
	p = *lst;
	while (p)
	{
		p = p->next;
		ft_lstdelone(t, del);
		t = p;
	}
	*lst = NULL;
}
