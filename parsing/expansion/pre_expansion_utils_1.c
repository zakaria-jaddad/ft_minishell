/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expansion_utils_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:53:06 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/03 22:55:02 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

t_list	*create_enhanced_tokens(t_list *tokens, bool is_dq)
{
	t_token	*tok;
	t_list	*new_token_node;
	t_list	*new_enhanced_tokens;

	if (tokens == NULL)
		return (NULL);
	new_enhanced_tokens = NULL;
	while (tokens)
	{
		tok = tokens->content;
		if (tok == NULL)
			return (ft_lstclear(&new_enhanced_tokens, free_token), NULL);
		if (is_dq == true)
			new_token_node = create_token_node(TOKEN_DOUBLE_QUOTE_WORD,
					tok->data);
		else
			new_token_node = create_token_node(tok->type, tok->data);
		if (new_token_node == NULL)
			return (ft_lstclear(&new_enhanced_tokens, free_token), NULL);
		ft_lstadd_back(&new_enhanced_tokens, new_token_node);
		tokens = tokens->next;
	}
	return (new_enhanced_tokens);
}

bool	check_cmdt(t_list *cmdt)
{
	t_list	*wordt;
	char	*word;
	t_list	*wordt_head;
	t_token	*tok;

	if (cmdt == NULL)
		return (false);
	wordt = get_tokenizd_word(&cmdt);
	if (wordt == NULL)
		return (false);
	wordt_head = wordt;
	word = tokens_to_str(wordt);
	if (word == NULL)
		return (ft_lstclear(&wordt, free), false);
	while (wordt)
	{
		tok = wordt->content;
		if (tok->type == TOKEN_DOUBLE_QUOTE_WORD
			|| tok->type == TOKEN_SINGLE_QUOTE_WORD)
			return (ft_lstclear(&wordt_head, free_token), true);
		wordt = wordt->next;
	}
	ft_lstclear(&wordt_head, free_token);
	return (false);
}
