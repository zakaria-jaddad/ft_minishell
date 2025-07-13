/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 03:39:01 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:35:33 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/syntax_check.h"

bool	syntax_check_escaping_norms(t_token *tok, t_list *t)
{
	if (is_logical_op(tok->type) == true)
	{
		if (check_logical_operator(t) == false)
			return (false);
	}
	else if (tok->type == TOKEN_PIPE)
	{
		if (check_pipe(t) == false)
			return (false);
	}
	else if (is_redirection(tok) == true)
	{
		if (check_redir(t) == false)
			return (false);
	}
	else if (tok->type == TOKEN_PAR_CLOSE)
		return (ft_fprintf(STDERR_FILENO, CLOSE_PER_SE), false);
	return (true);
}

bool	check_per(t_list *tokens)
{
	if (tokens == NULL)
		return (false);
	if (peak_prev(tokens) == TOKEN_PAR_CLOSE)
		return (ft_fprintf(STDERR_FILENO, OPEN_PER_SE), false);
	return (true);
}

bool	syntax_check(t_list *t)
{
	t_token	*tok;
	t_list	*subshell;

	if (t == NULL)
		return (false);
	while (t)
	{
		tok = t->content;
		if (tok->type == TOKEN_PAR_OPEN)
		{
			if (check_per(t) == false)
				return (false);
			subshell = get_subshell(&t);
			if (syntax_check(subshell) == false)
				return (ft_lstclear(&subshell, free_token), false);
			ft_lstclear(&subshell, free_token);
			continue ;
		}
		if (syntax_check_escaping_norms(tok, t) == false)
			return (false);
		if (t != NULL)
			t = t->next;
	}
	return (true);
}
