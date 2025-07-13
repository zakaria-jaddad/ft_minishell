/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:23:10 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 00:22:42 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/ast.h"

static void	skip_par(t_list **tokens)
{
	int		depth;
	t_token	*token;

	depth = 0;
	if (tokens == NULL)
		return ;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->type == TOKEN_PAR_OPEN)
			depth++;
		else if (token->type == TOKEN_PAR_CLOSE)
		{
			depth--;
			if (depth == 0)
			{
				(*tokens) = (*tokens)->next;
				break ;
			}
		}
		(*tokens) = (*tokens)->next;
	}
}

static t_list	*check_token(t_list *tokens, t_token_type token_type)
{
	t_token	*token;

	while (tokens && tokens->content)
	{
		token = tokens->content;
		if (token->type == TOKEN_PAR_OPEN)
		{
			skip_par(&tokens);
			continue ;
		}
		if (token->type == token_type)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

static t_list	*check_redirection(t_list *tokens)
{
	t_token	*token;

	while (tokens && tokens->content)
	{
		token = tokens->content;
		if (token->type == TOKEN_PAR_OPEN)
		{
			skip_par(&tokens);
			continue ;
		}
		if (token->type == TOKEN_IN_REDIR)
			return (tokens);
		if (token->type == TOKEN_OUT_REDIR)
			return (tokens);
		if (token->type == TOKEN_HEREDOC)
			return (tokens);
		if (token->type == TOKEN_APPEND_REDIR)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

/*
 * @brief get root function get the roo token from the given tokens
 */
t_list	*get_root(t_list *tokens)
{
	if (check_token(tokens, TOKEN_IF_AND) != NULL)
		return (check_token(tokens, TOKEN_IF_AND));
	if (check_token(tokens, TOKEN_IF_OR) != NULL)
		return (check_token(tokens, TOKEN_IF_OR));
	if (check_token(tokens, TOKEN_PIPE) != NULL)
		return (check_token(tokens, TOKEN_PIPE));
	if (check_redirection(tokens) != NULL)
		return (check_redirection(tokens));
	return (NULL);
}
