/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:03:20 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/23 18:09:22 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

bool	is_valid_dollar_with_qs_next(t_list *current_token_node)
{
	t_token	*current_token;

	if (current_token_node == NULL)
		return (false);
	current_token = current_token_node->content;
	if (current_token == NULL)
		return (false);
	return (ft_strcmp(current_token->data, "$") == 0
		&& check_token_type(current_token, TOKEN_WORD)
		&& (peak_next(current_token_node) == TOKEN_DOUBLE_QUOTE_WORD
			|| peak_next(current_token_node) == TOKEN_SINGLE_QUOTE_WORD));
}

bool	is_valid_dollar_with_valid_var(t_list *current_token_node)
{
	t_token	*current_token;
	t_list	*next_token_node;
	t_token	*next_token;

	if (current_token_node == NULL)
		return (false);
	next_token_node = current_token_node->next;
	if (next_token_node == NULL)
		return (false);
	current_token = current_token_node->content;
	next_token = next_token_node->content;
	if (current_token == NULL || next_token == NULL)
		return (false);
	if (ft_strchr(special_expansion, *next_token->data) != NULL)
		return false;
	return (ft_strcmp(current_token->data, "$") == 0
		&& ft_strcmp(next_token->data, "$") != 0
		&& (check_token_type(current_token, TOKEN_WORD)
			|| check_token_type(current_token, TOKEN_DOUBLE_QUOTE_WORD))
		&& peak_next(current_token_node) == current_token->type);
}

bool	is_valid_dollar_with_dollar(t_list *current_token_node)
{
	t_token	*current_token;
	t_list	*next_token_node;
	t_token	*next_token;

	if (current_token_node == NULL)
		return (false);
	next_token_node = current_token_node->next;
	if (next_token_node == NULL)
		return (false);
	current_token = current_token_node->content;
	next_token = next_token_node->content;
	if (current_token == NULL || next_token == NULL)
		return (false);
	return (ft_strcmp(current_token->data, "$") == 0
		&& ft_strcmp(next_token->data, "$") == 0);
}
