/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:56:36 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/03 23:50:04 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

t_list	*expand_word(t_list *wordt, t_list *env)
{
	t_list	*expanded_tokenized_word;
	t_list	*expansion_lst;

	if (wordt == NULL || env == NULL)
		return (NULL);
	expanded_tokenized_word = expand(wordt, env);
	if (expanded_tokenized_word == NULL)
		return (NULL);
	expansion_lst = extract_words_list(expanded_tokenized_word);
	return (expansion_lst);
}
