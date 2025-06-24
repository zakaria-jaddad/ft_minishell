/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:32:40 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/24 11:59:31 by zajaddad         ###   ########.fr       */
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
	t_token	*current_token;

	if (current_token_node == NULL)
		return ;
	current_token = current_token_node->content;
	if (current_token == NULL)
		return ;
	if (ft_isdigit(*current_token->data) == true)
		return (digit_expansion(&current_token->data));
	word_expansion(&current_token->data, env);
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

void	expand_dollar(t_list **tokens, t_list *env)
{
	t_list	*tokens_head;
	t_token	*current_token;

	if (tokens == NULL)
		return ;
	tokens_head = *tokens;
	while (*tokens)
	{
		current_token = (*tokens)->content;
		if (ft_strchr(current_token->data, '$') != NULL)
		{
			if (is_valid_dollar_with_qs_next(*tokens) == true
				|| is_valid_dollar_with_valid_var(*tokens) == true)
			{
				expand_dollar_escaping_norms(tokens, &tokens_head, env);
				continue ;
			}
			else if (is_valid_dollar_with_dollar(*tokens) == true)
				*tokens = (*tokens)->next;
		}
		if (*tokens == NULL)
			break ;
		*tokens = (*tokens)->next;
	}
	*tokens = tokens_head;
}
