/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:13:15 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/15 11:23:18 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/tokenize.h"

bool	is_redirection(t_token *token)
{
	if (token == NULL)
		return (false);
	return (token->type == TOKEN_IN_REDIR || token->type == TOKEN_OUT_REDIR
		|| token->type == TOKEN_APPEND_REDIR || token->type == TOKEN_HEREDOC);
}

bool	check_token_type(t_token *token, t_token_type token_type)
{
	if (token == NULL)
		return (false);
	return (token->type == token_type);
}

bool	is_word(t_token *token)
{
	if (token == NULL)
		return (false);
	return (token->type == TOKEN_WORD || token->type == TOKEN_DOUBLE_QUOTE_WORD
		|| token->type == TOKEN_SINGLE_QUOTE_WORD);
}

bool	is_token_special(t_token *token)
{
	if (token == NULL)
		return (false);
	return (!(is_word(token) || check_token_type(token, TOKEN_WHITE_SPACE)));
}
