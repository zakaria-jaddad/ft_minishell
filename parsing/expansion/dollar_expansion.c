/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:32:40 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/14 18:54:33 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

static void	del_node_and_go_next(t_list **tokens, t_list **token_head)
{
	t_list	*node_to_del;

	if (tokens == NULL || *tokens == NULL)
		return ;
	if (token_head == NULL || *token_head == NULL)
		return ;
	node_to_del = *tokens;
	*tokens = (*tokens)->next;
	ft_lst_rm_one(token_head, node_to_del, free_token);
}

static void	update_current_token(t_list *current_token_node, t_list *env)
{
	t_token	*tok;

	if (current_token_node == NULL)
		return ;
	tok = current_token_node->content;
	if (tok == NULL)
		return ;
	if (ft_isdigit(*tok->data) == true)
		return (digit_expansion(&tok->data));
	word_expansion(&tok->data, env);
}

static void	expand_dollar_escaping_norms(t_list **tokens, t_list **tokens_head,
		t_list *env)
{
	if (is_valid_dollar_with_qs_next(*tokens) == true)
		del_node_and_go_next(tokens, tokens_head);
	else if (is_valid_dollar_with_valid_var(*tokens) == true)
		(void)(del_node_and_go_next(tokens, tokens_head),
			update_current_token(*tokens, env));
}

void	c_null_tokens(t_list **tokens)
{
	t_list	*th;
	t_token	*tok;
	t_list	*node_to_del;

	if (tokens == NULL || *tokens == NULL)
		return ;
	th = *tokens;
	while (th && th->content)
	{
		tok = th->content;
		if (tok->data == NULL)
		{
			if (tok->type == TOKEN_DOUBLE_QUOTE_WORD || tok->type == TOKEN_SINGLE_QUOTE_WORD)
				tok->data = ft_strdup("");
			else
			{
				node_to_del = th;
				th = th->next;
				ft_lst_rm_one(tokens, node_to_del, free_token);
				continue ;
			}
		}
		th = th->next;
	}
}

void	expand_dollar(t_list **tokens, t_list *env)
{
	t_list	*th;
	t_token	*tok;

	if (tokens == NULL)
		return ;
	th = *tokens;
	while (*tokens && (*tokens)->content)
	{
		tok = (*tokens)->content;
		if (tok && tok->data && ft_strchr(tok->data, '$') != NULL)
		{
			if (is_valid_dollar_with_qs_next(*tokens) == true
				|| is_valid_dollar_with_valid_var(*tokens) == true)
			{
				expand_dollar_escaping_norms(tokens, &th, env);
				continue ;
			}
			else if (is_valid_dollar_with_dollar(*tokens) == true)
				*tokens = (*tokens)->next;
		}
		if (*tokens == NULL)
			break ;
		*tokens = (*tokens)->next;
	}
	(void)!(*tokens = th, c_null_tokens(tokens), 0);
}
