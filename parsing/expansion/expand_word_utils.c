/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:48:35 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/04 00:36:56 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

int	count_spaces(char *s)
{
	int	spaces;

	spaces = 0;
	while (*s)
	{
		if (*s == ' ')
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

static bool	check_spaces(char *str)
{
	return (count_spaces(str) == (int)ft_strlen(str));
}

static void	*extract_words_list_escapint_norms(t_list **result, t_list **tokens)
{
	t_list	*tokenized_word;
	char	*dup;
	t_list	*new_node;

	tokenized_word = get_filename(tokens);
	if (tokenized_word == NULL)
		return (ft_lstclear(result, free), NULL);
	dup = tokens_to_str(tokenized_word);
	ft_lstclear(&tokenized_word, free_token);
	if (dup == NULL)
		return (ft_lstclear(result,
				free), NULL);
	new_node = ft_lstnew(dup);
	if (new_node == NULL)
		return (free(dup),ft_lstclear(result, free), NULL);
	ft_lstadd_back(result, new_node);
	return (NOTNULL);
}

t_list	*extract_words_list(t_list *tokens)
{
	t_list	*result;
	t_token	*tok;

	result = NULL;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok && is_valid_word_token(tok->type) && tok->data
			&& check_spaces(tok->data) == false)
		{
			if (extract_words_list_escapint_norms(&result, &tokens) == NULL)
				return (NULL);
			continue ;
		}
		tokens = tokens->next;
	}
	return (result);
}
