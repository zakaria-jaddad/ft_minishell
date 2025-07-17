/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_logical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 03:33:17 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/17 06:02:39 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/syntax_check.h"

bool	check_logical_operator(t_list *tokens)
{
	t_token_type	next;
	t_token_type	prev;
	t_token			*tok;

	if (tokens == NULL)
		return (false);
	next = peak_next(tokens);
	prev = peak_prev(tokens);
	tok = tokens->content;
	if (prev != TOKEN_PAR_CLOSE && is_type_word(prev) != true)
		return (ft_fprintf(STDERR_FILENO, SYNTAX_E, tok->data), false);
	if (next != TOKEN_PAR_OPEN && is_type_word(next) != true
		&& is_type_redirection(next) == false)
		return (ft_fprintf(STDERR_FILENO, SYNTAX_E, tok->data), false);
	return (true);
}
