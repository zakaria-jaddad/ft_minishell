/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:44:31 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/18 01:17:23 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"
#include <stdio.h>

static bool	if_escape(t_token *tok)
{
	return (is_word_and_space_found(tok)
		&& count_spaces(tok->data) != (int)ft_strlen(tok->data));
}

void	split_enhanced_tokens(t_list **tokens)
{
	t_list	*tokens_tmp;
	t_token	*tok;
	t_list	*wordt;

	tokens_tmp = *tokens;
	while (tokens_tmp)
	{
		tok = tokens_tmp->content;
		if (if_escape(tok))
		{
			wordt = get_word_tokens(tok);
			if (wordt == NULL)
				return ;
			ist(tokens, &tokens_tmp, wordt);
			continue ;
		}
		else if (tok->data == NULL || (tok->type == TOKEN_WORD
				&& count_spaces(tok->data) == (int)ft_strlen(tok->data)))
		{
			del_token(&tokens_tmp, tokens);
			continue ;
		}
		tokens_tmp = tokens_tmp->next;
	}
}

t_list	*expand(t_list *tokens, t_list *env)
{
	t_list	*enhanced_tokens;
	t_list	*tmp;

	enhanced_tokens = get_enhanced_tokens(tokens, "$*");
	if (enhanced_tokens == NULL)
		return (NULL);
	expand_dollar(&enhanced_tokens, env);
	tmp = enhanced_tokens;
	enhanced_tokens = get_enhanced_tokens(enhanced_tokens, "*");
	ft_lstclear(&tmp, free_token);
	if (enhanced_tokens == NULL)
		return (NULL);
	tmp = expand_wildcard(enhanced_tokens);
	if (tmp == NULL)
	{
		if (enhanced_tokens == NULL)
			return (NULL);
		split_enhanced_tokens(&enhanced_tokens);
		return (enhanced_tokens);
	}
	ft_lstclear(&enhanced_tokens, free_token);
	return (tmp);
}
