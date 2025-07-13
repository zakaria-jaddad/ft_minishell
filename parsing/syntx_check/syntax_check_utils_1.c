/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 03:26:20 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:35:40 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/syntax_check.h"

bool	is_logical_op(t_token_type type)
{
	return (type == TOKEN_IF_AND || type == TOKEN_IF_OR);
}

bool	is_type_word(t_token_type type)
{
	return (type == TOKEN_WORD || type == TOKEN_DOUBLE_QUOTE_WORD
		|| type == TOKEN_SINGLE_QUOTE_WORD);
}

bool	is_type_redirection(t_token_type type)
{
	return (type == TOKEN_IN_REDIR || type == TOKEN_OUT_REDIR
		|| type == TOKEN_APPEND_REDIR || type == TOKEN_HEREDOC);
}

char	*get_redir_type(t_token *tok)
{
	if (tok->type == TOKEN_HEREDOC)
		return ("<<");
	if (tok->type == TOKEN_APPEND_REDIR)
		return (">>");
	if (tok->type == TOKEN_IN_REDIR)
		return ("<");
	else
		return (">");
}

char	*get_td_from_tt(t_token_type t)
{
	if (t == TOKEN_PAR_OPEN)
		return ("(");
	else if (t == TOKEN_PAR_CLOSE)
		return (")");
	else if (t == TOKEN_PIPE)
		return ("|");
	else if (t == TOKEN_IN_REDIR)
		return ("<");
	else if (t == TOKEN_OUT_REDIR)
		return (">");
	else if (t == TOKEN_IF_AND)
		return ("&&");
	else if (t == TOKEN_IF_OR)
		return ("||");
	else if (t == TOKEN_HEREDOC)
		return ("<<");
	else
		return (">>");
}
