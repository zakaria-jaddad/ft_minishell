/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:44:31 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:01:17 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"
#include <stdio.h>

static bool	is_ws_found(char *s)
{
	return (ft_strcmp(s, " ") == 0 || ft_strcmp(s, "\t") == 0);
}

static bool	if_escape(t_token *tok)
{
	return (is_word_and_space_found(tok)
		&& count_spaces(tok->data) != (int)ft_strlen(tok->data));
}

t_list	*get_word_tokens(t_token *token)
{
	t_list	*sptw;
	t_list	*wordt;
	t_list	*wordt_node;
	t_list	*sptw_head;

	if (token == NULL)
		return (NULL);
	sptw = ft_split_pro_max(token->data, " \t\n");
	(void)!(sptw_head = sptw, wordt = NULL);
	if (sptw == NULL)
		return (NULL);
	while (sptw && sptw->content)
	{
		if (is_ws_found(sptw->content))
			wordt_node = create_token_node(TOKEN_WHITE_SPACE, " ");
		else
			wordt_node = create_token_node(TOKEN_WORD, sptw->content);
		if (wordt_node == NULL)
			return (ft_lstclear(&sptw_head, free), ft_lstclear(&wordt,
					free_token), NULL);
		ft_lstadd_back(&wordt, wordt_node);
		sptw = sptw->next;
	}
	return (ft_lstclear(&sptw_head, free), wordt);
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
			if (wordt == NULL && ist(tokens, &tokens_tmp, wordt))
				return ;
			continue ;
		}
		else if (tok->data == NULL)
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

	enhanced_tokens = get_enhanced_tokens(tokens, "$");
	if (enhanced_tokens == NULL)
		return (NULL);
	expand_dollar(&enhanced_tokens, env);
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
