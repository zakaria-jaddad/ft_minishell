/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:06:04 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 02:04:34 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/tokenize.h"

void	remove_es(t_list **tokens)
{
	t_list	*th;
	t_list	*tt;
	t_token	*token;

	if (tokens == NULL)
		return ;
	th = *tokens;
	while (th)
	{
		token = th->content;
		if ((token->type == TOKEN_DOUBLE_QUOTE_WORD
				|| token->type == TOKEN_SINGLE_QUOTE_WORD)
			&& token->data != NULL && *token->data == 0)
		{
			(void)!(tt = th, th = th->next, ft_lst_rm_one(tokens, tt,
					free_token), 0);
			continue ;
		}
		if (th == NULL)
			return ;
		th = th->next;
	}
}

bool	is_wrapped_by_single_paren_pair(t_list *tokens)
{
	t_list	*token_node;
	int		depth;

	if (tokens == NULL)
		return (false);
	if (check_token_type(tokens->content, TOKEN_PAR_OPEN) == false)
		return (false);
	token_node = tokens->next;
	depth = 1;
	while (token_node && token_node->next)
	{
		if (check_token_type(token_node->content, TOKEN_PAR_OPEN))
			depth++;
		else if (check_token_type(token_node->content, TOKEN_PAR_CLOSE))
			depth--;
		if (depth == 0 && token_node->next)
			return (false);
		token_node = token_node->next;
	}
	if (depth == 1 && check_token_type(token_node->content, TOKEN_PAR_CLOSE))
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

t_list	*dup_tokens(t_list *ts, t_list *te, bool al)
{
	t_list	*nt;
	t_list	*tn;
	t_token	*t;

	if (ts == NULL || te == NULL)
		return (NULL);
	(void)!(nt = NULL, t = NULL);
	while (ts && ts != te && ts->content)
	{
		t = ts->content;
		tn = create_token_node(t->type, t->data);
		if (tn == NULL)
			return (ft_lstclear(&nt, free_token), NULL);
		ft_lstadd_back(&nt, tn);
		ts = ts->next;
	}
	if (ts != NULL && al == true)
	{
		(void)!(t = ts->content, tn = create_token_node(t->type, t->data));
		if (tn == NULL)
			return (ft_lstclear(&nt, free_token), NULL);
		ft_lstadd_back(&nt, tn);
	}
	return (nt);
}

char	*get_token_data(t_token *token)
{
	if (token == NULL)
		return (NULL);
	return (token->data);
}
