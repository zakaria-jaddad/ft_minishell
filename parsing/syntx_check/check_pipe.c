/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 03:32:13 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:33:06 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/syntax_check.h"

bool	check_pipe(t_list *tokens)
{
	t_token_type	next;
	t_token_type	prev;

	if (tokens == NULL)
		return (false);
	next = peak_next(tokens);
	prev = peak_prev(tokens);
	if (prev == INVALID_TOKEN || next == INVALID_TOKEN)
		return (ft_fprintf(STDERR_FILENO, PIPE_SE), false);
	if (is_type_word(prev) == false && prev != TOKEN_PAR_CLOSE)
		return (ft_fprintf(STDERR_FILENO, PIPE_SE), false);
	if (is_type_word(next) == false && is_type_redirection(next == false)
		&& next != TOKEN_PAR_OPEN)
		return (ft_fprintf(STDERR_FILENO, PIPE_SE), false);
	return (true);
}
