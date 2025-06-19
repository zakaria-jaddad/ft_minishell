/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:01:57 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/19 08:21:16 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/parsing.h"

void	remove_front_spaces(t_list **tokens)
{
	t_list	*curr;
	t_list	*next;
	t_token	*token;

	if (!tokens || !*tokens)
		return ;
	curr = *tokens;
	while (curr)
	{
		token = curr->content;
		if (token->type != TOKEN_WHITE_SPACE)
			break ;
		next = curr->next;
		if (next)
			next->prev = NULL;
		ft_lst_rm_one(curr, free_token);
		curr = next;
	}
	*tokens = curr;
}

void	remove_back_spaces(t_list **tokens)
{
	t_token	*token;
	t_list	*curr;
	t_list	*prev;

	if (!tokens || !*tokens)
		return ;
	curr = ft_lstlast(*tokens);
	while (curr)
	{
		token = (t_token *)curr->content;
		if (token->type != TOKEN_WHITE_SPACE)
			break ;
		prev = curr->prev;
		if (prev)
			prev->next = NULL;
		else
			*tokens = NULL;
		curr->prev = NULL;
		curr->next = NULL;
		ft_lstdelone(curr, free_token);
		curr = prev;
	}
}

void	skip_front_spaces(t_list **tokens)
{
	t_token	*token;

	if (tokens == NULL || *tokens == NULL)
		return ;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token == NULL || token->type != TOKEN_WHITE_SPACE)
			break ;
		*tokens = (*tokens)->next;
	}
}

void	skip_prev_spaces(t_list **tokens)
{
	t_token	*token;

	if (tokens == NULL || *tokens == NULL)
		return ;
	while (*tokens != NULL)
	{
		token = (t_token *)(*tokens)->content;
		if (token == NULL || token->type != TOKEN_WHITE_SPACE)
			break ;
		*tokens = (*tokens)->prev;
	}
}

t_list *get_filename(t_list **tokens)
{
	t_list *filename;
	t_list *token_node;
	t_token *token;

	filename = NULL;
	token_node = NULL;
	token = NULL;
	if (tokens == NULL)
		return (NULL);
	skip_front_spaces(tokens);
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->type != TOKEN_WORD
			&& token->type != TOKEN_DOUBLE_QUOTE_WORD
			&& token->type != TOKEN_SINGLE_QUOTE_WORD)
			break;
		token_node = create_token_node(token->type, token->data);
		ft_lstadd_back(&filename, token_node);
		*tokens = (*tokens)->next;
	}
	return (filename);
}
