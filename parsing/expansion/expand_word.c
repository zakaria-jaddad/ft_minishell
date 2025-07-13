/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:56:36 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 00:30:15 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"
#include <stdio.h>

t_list	*expand_word(t_list *wordt, t_list *env)
{
	t_list	*expanded_wordt;
	t_list	*expansion_lst;

	if (wordt == NULL || env == NULL)
		return (NULL);
	expanded_wordt = expand(wordt, env);
	if (expanded_wordt == NULL)
		return (NULL);
	expansion_lst = extract_words_list(expanded_wordt);
	ft_lstclear(&expanded_wordt, free_token);
	return (expansion_lst);
}
