/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfirst_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:20:52 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/18 01:05:30 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list  *ft_lstfirst(t_list *lst)
{
      	if (lst == NULL)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);  
}

