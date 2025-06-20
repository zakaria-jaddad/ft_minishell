/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:06:04 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/20 07:01:23 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/parsing.h"
#include <stdio.h>

void	remove_es(t_list **tokens)
{
	t_list	*th;
	t_list	*tt;
	t_token	*token;
	int		lst_size;

	if (tokens == NULL)
		return ;
	(th = *tokens, lst_size = ft_lstsize(*tokens));
	while (th)
	{
		token = th->content;
		if ((token->type == TOKEN_DOUBLE_QUOTE_WORD
				|| token->type == TOKEN_SINGLE_QUOTE_WORD)
			&& token->data != NULL && *token->data == 0)
		{
			(tt = th, th = th->next, ft_lst_rm_one(tt, free_token));
			lst_size--;
			continue ;
		}
		if (th == NULL)
			return ;
		th = th->next;
	}
	if (lst_size == 0)
		*tokens = NULL;
}

bool	is_between_per(t_list *tokens)
{
	t_list	*first_token_node;
	t_list	*last_token_node;

	if (tokens == NULL)
		return (false);
	first_token_node = tokens;
	last_token_node = ft_lstlast(tokens);
	if (last_token_node == NULL)
		return (false);
	if (check_token_type(first_token_node->content, TOKEN_PAR_OPEN)
		&& check_token_type(last_token_node->content, TOKEN_PAR_CLOSE))
		return (true);
	return (false);
}

void	remove_per(t_list **tokens)
{
	t_list	*first;
	t_list	*last;

	if (tokens == NULL || *tokens == NULL)
		return ;
	first = *tokens;
	*tokens = first->next;
	if (*tokens != NULL)
		(*tokens)->prev = NULL;
	first->next = NULL;
	first->prev = NULL;
	ft_lstdelone(first, free_token);
	if (*tokens == NULL)
		return ;
	last = ft_lstlast(*tokens);
	if (last->prev != NULL)
		last->prev->next = NULL;
	else
		*tokens = NULL;
	last->prev = NULL;
	last->next = NULL;
	ft_lstdelone(last, free_token);
}

t_list *dup_tokens(t_list *tokens_start, t_list *token_end, bool add_last)
{
	t_list *new_tokens;
	t_list *token_node;
	t_token *token;

        if (tokens_start == NULL || token_end == NULL)
                return (NULL);

	(new_tokens = NULL, token = NULL);
	while (tokens_start && tokens_start != token_end)
        {
		token = tokens_start->content;
		if (token == NULL)
			return (ft_lstclear(&new_tokens, free_token), NULL);
		token_node = create_token_node(token->type, token->data);
		if (token_node == NULL)
			return (ft_lstclear(&new_tokens, free_token), NULL);
		ft_lstadd_back(&new_tokens, token_node);
		tokens_start = tokens_start->next;
	}
	if (tokens_start != NULL && add_last == true)
	{
		token = tokens_start->content;
		token_node = create_token_node(token->type, token->data);
		if (token_node == NULL)
			return (ft_lstclear(&new_tokens, free_token), NULL);
		ft_lstadd_back(&new_tokens, token_node);
	}
	return new_tokens;
}
