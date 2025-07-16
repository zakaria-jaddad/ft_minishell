/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pro_max.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:48:03 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/22 17:48:28 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*remove_dup(t_list *lst, char *charset)
{
	t_list	*new_lst;
	char	current_delim;
	t_list	*node;

	if (lst == NULL || charset == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		if (ft_strchr(charset, *((char *)lst->content)) != NULL)
		{
			current_delim = *((char *)lst->content);
			node = ft_lstnew(ft_strdup(lst->content));
			if (node == NULL)
				return (ft_lstclear(&new_lst, free), NULL);
			ft_lstadd_back(&new_lst, node);
			lst = lst->next;
			while (lst != NULL && *((char *)lst->content) == current_delim)
				lst = lst->next;
			continue ;
		}
		node = ft_lstnew(ft_strdup(lst->content));
		if (node == NULL)
			return (ft_lstclear(&new_lst, free), NULL);
		ft_lstadd_back(&new_lst, node);
		if (lst == NULL)
			break ;
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
