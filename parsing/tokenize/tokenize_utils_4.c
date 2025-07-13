/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:24:50 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:55:34 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/tokenize.h"
#include <stdio.h>

/*
 * @brief Get the type of the next non white space token
 * @return
 *      On Error return INVALID_TOKEN
 */
t_token_type	peak_next(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL)
		return (INVALID_TOKEN);
	tokens = tokens->next;
	skip_front_spaces(&tokens);
	if (tokens == NULL)
		return (INVALID_TOKEN);
	token = tokens->content;
	if (token == NULL)
		return (INVALID_TOKEN);
	return (token->type);
}

/*
 * @brief Get the type of the previous non white space token
 * @return
 *      On Error return INVALID_TOKEN
 */
t_token_type	peak_prev(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL)
		return (INVALID_TOKEN);
	tokens = tokens->prev;
	skip_prev_spaces(&tokens);
	if (tokens == NULL)
		return (INVALID_TOKEN);
	token = tokens->content;
	if (token == NULL)
		return (INVALID_TOKEN);
	return (token->type);
}

t_list	*append_tokens(t_list **tokens, t_token_type token_type,
		char *token_data)
{
	t_list	*token_node;

	if (token_data == NULL || tokens == NULL)
		return (NULL);
	token_node = create_token_node(token_type, token_data);
	if (token_node == NULL)
		return (NULL);
	ft_lstadd_back(tokens, token_node);
	return (token_node);
}

t_list	*insert_tokens(t_list **tokens, t_token_type token_type,
		char *token_data)
{
	t_list	*token_node;

	if (token_data == NULL || tokens == NULL)
		return (NULL);
	token_node = create_token_node(token_type, token_data);
	if (token_node == NULL)
		return (NULL);
	ft_lstadd_front(tokens, token_node);
	return (token_node);
}

/*
 * @brief Duplicate tokens Untile special token
 *      Each token duplicated get remove from the original list
 * Special Token : && || | > < >> <<
 *
 * @var:
 *      - dtn: dup_simple_tokens
 */
t_list	*dup_and_remove_simple_tokens(t_list *to_start)
{
	t_list	*simple_tokens;
	t_list	*dsn;
	t_list	*node_to_del;
	t_token	*token;

	if (to_start == NULL)
		return (NULL);
	(void)!(simple_tokens = NULL, token = NULL, node_to_del = NULL);
	while (to_start)
	{
		token = to_start->content;
		if (is_token_special(token) == true)
			break ;
		dsn = create_token_node(token->type, token->data);
		if (dsn == NULL)
			return (ft_lstclear(&simple_tokens, free_token), NULL);
		ft_lstadd_back(&simple_tokens, dsn);
		if (append_tokens(&simple_tokens, TOKEN_WHITE_SPACE, " ") == NULL)
			return (ft_lstclear(&simple_tokens, free_token), NULL);
		(void)!(node_to_del = to_start, to_start = to_start->next);
		ft_lst_rm_one(NULL, node_to_del, free_token);
	}
	if (insert_tokens(&simple_tokens, TOKEN_WHITE_SPACE, " ") == NULL)
		return (ft_lstclear(&simple_tokens, free_token), NULL);
	return (simple_tokens);
}
