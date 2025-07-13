/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:48:35 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 00:30:23 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"
#include <stdio.h>

int	count_spaces(char *s)
{
	int	spaces;

	spaces = 0;
	while (*s)
	{
		if (*s == ' ' || *s == '\t')
			spaces++;
		s++;
	}
	return (spaces);
}

static int	is_valid_word_token(int type)
{
	return (type == TOKEN_WORD || type == TOKEN_DOUBLE_QUOTE_WORD
		|| type == TOKEN_SINGLE_QUOTE_WORD);
}

static void	*extract_words_list_escaping_norms(t_list **result, t_list **tokens)
{
	t_list	*wordt;
	char	*dup;
	t_list	*new_node;

	wordt = get_filename(tokens);
	if (wordt == NULL)
		return (ft_lstclear(result, free), NULL);
	dup = tokens_to_str(wordt);
	ft_lstclear(&wordt, free_token);
	if (dup == NULL)
		return (ft_lstclear(result, free), NULL);
	new_node = ft_lstnew(dup);
	if (new_node == NULL)
		return (free(dup), ft_lstclear(result, free), NULL);
	ft_lstadd_back(result, new_node);
	return (NOTNULL);
}

t_list	*extract_words_list(t_list *tokens)
{
	t_list	*result;
	t_token	*tok;

	result = NULL;
	while (tokens && tokens->content)
	{
		tok = (t_token *)tokens->content;
		if (is_valid_word_token(tok->type) && tok->data)
		{
			if (extract_words_list_escaping_norms(&result, &tokens) == NULL)
				return (NULL);
			continue ;
		}
		tokens = tokens->next;
	}
	return (result);
}
