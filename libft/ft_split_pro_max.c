/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pro_max.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:48:03 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/17 05:59:25 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	remove_dup_escaping_norms(t_list **new_lst, t_list *lst)
{
	t_list	*node;
	char	*str;

	str = ft_strdup(lst->content);
	node = ft_lstnew(str);
	if (node == NULL)
		return (free(str), ft_lstclear(new_lst, free), false);
	ft_lstadd_back(new_lst, node);
	return (true);
}

static t_list	*remove_dup(t_list *lst, char *charset)
{
	char	current_delim;
	t_list	*new_lst;

	if (lst == NULL || charset == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst && lst->content)
	{
		if (ft_strchr(charset, *((char *)lst->content)) != NULL)
		{
			if (remove_dup_escaping_norms(&new_lst, lst) == false)
				return (NULL);
			current_delim = *((char *)lst->content);
			lst = lst->next;
			while (lst != NULL && *((char *)lst->content) == current_delim)
				lst = lst->next;
			continue ;
		}
		if (remove_dup_escaping_norms(&new_lst, lst) == false)
			return (NULL);
		if (lst != NULL)
			lst = lst->next;
	}
	return (new_lst);
}

t_list	*ft_split_pro_max(char *str, char *charset)
{
	t_list	*lst;
	t_list	*new_lst;

	if (str == NULL || charset == NULL)
		return (NULL);
	lst = ft_split_pro(str, charset);
	if (lst == NULL)
		return (NULL);
	new_lst = remove_dup(lst, charset);
	if (new_lst == NULL)
		return (ft_lstclear(&lst, free), NULL);
	ft_lstclear(&lst, free);
	return (new_lst);
}
