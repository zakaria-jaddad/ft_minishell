/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 03:27:58 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/14 17:49:05 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	append_prev_word(t_list **lst, char *line, int i, int prev)
{
	char	*word;
	t_list	*node;

	if (i == prev)
		return ;
	word = ft_substr(line, 0, i - prev);
	if (word == NULL)
		return (ft_lstclear(lst, free));
	node = ft_lstnew(word);
	if (node == NULL)
		return (ft_lstclear(lst, free));
	ft_lstadd_back(lst, node);
}

static void	append_special(t_list **lst, char *special, int *i, int *prev)
{
	t_list	*node;

	special = ft_strdup(special);
	if (special == NULL)
		return (ft_lstclear(lst, free));
	node = ft_lstnew(special);
	if (node == NULL)
		return (ft_lstclear(lst, free));
	ft_lstadd_back(lst, node);
	*i += ft_strlen(special);
	*prev = *i;
}

t_list	*ft_split_pro(char *str, char *charset)
{
	t_list	*lst;
	int		i;
	int		prev;

	i = 0;
        prev = 0;
	lst = NULL;
        if (str == NULL || charset == NULL)
                return (NULL);
	while (str[i])
        {
                if (ft_strchr(charset, str[i]) != NULL)
                		(append_prev_word(&lst, &str[prev], i, prev), append_special(&lst,
				ft_substr(&str[i], 0, 1), &i, &prev));
                else
                        i++;
        }
	if (str[i] == 0)
		(append_prev_word(&lst, &str[prev], i, prev));
	return (lst);
}
