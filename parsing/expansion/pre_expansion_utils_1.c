/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expansion_utils_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:53:06 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/14 09:03:50 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"
#include <stdbool.h>

t_list	*create_enhanced_tokens(t_list *tokens, bool is_dq)
{
	t_token	*tok;
	t_list	*ntn;
	t_list	*net;

	if (tokens == NULL)
		return (NULL);
	net = NULL;
	while (tokens)
	{
		tok = tokens->content;
		if (tok == NULL)
			return (ft_lstclear(&net, free_token), NULL);
		if (is_dq == true && tok->type != TOKEN_SINGLE_QUOTE_WORD)
			ntn = create_token_node(TOKEN_DOUBLE_QUOTE_WORD, tok->data);
		else
			ntn = create_token_node(tok->type, tok->data);
		if (ntn == NULL)
			return (ft_lstclear(&net, free_token), NULL);
		ft_lstadd_back(&net, ntn);
		tokens = tokens->next;
	}
	return (net);
}

bool	check_cmdt(t_list *cmdt)
{
	t_list	*wordt;
	t_list	*wordt_head;
	t_token	*tok;
	char	*str;

	if (cmdt == NULL)
		return (false);
	wordt = get_tokenizd_word(&cmdt);
	if (wordt == NULL)
		return (false);
	wordt_head = wordt;
	str = tokens_to_str(wordt);
	if (str != NULL && ft_strcmp(str, "export") != 0)
		return (free(str), ft_lstclear(&wordt_head, free_token), true);
	free(str);
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
