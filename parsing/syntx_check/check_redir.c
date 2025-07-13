/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 03:31:02 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:34:00 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/syntax_check.h"

bool	check_redir(t_list *tokens)
{
	t_token_type	prev;
	t_token_type	next;
	char			*redir_type;

	if (tokens == NULL)
		return (false);
	redir_type = get_redir_type(tokens->content);
	prev = peak_prev(tokens);
	next = peak_next(tokens);
	if (next == INVALID_TOKEN)
		return (ft_fprintf(STDERR_FILENO, SYNTAX_E, redir_type), false);
	if (prev != TOKEN_PIPE && prev != TOKEN_IF_AND && prev != TOKEN_IF_OR
		&& prev != TOKEN_PAR_OPEN && prev != TOKEN_PAR_CLOSE
		&& is_type_word(prev) == false && prev != INVALID_TOKEN)
		return (ft_fprintf(STDERR_FILENO, SYNTAX_E, redir_type), false);
	if (is_type_word(next) == false)
		return (ft_fprintf(STDERR_FILENO, SYNTAX_E, get_td_from_tt(next)),
			false);
	return (true);
}
