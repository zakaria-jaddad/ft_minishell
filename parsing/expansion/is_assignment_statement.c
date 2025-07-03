/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_assignment_statement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:50:18 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/03 22:50:56 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

static bool	key_validation(t_list *tokens)
{
	t_token	*tok;

	if (tokens == NULL)
		return (false);
	while (tokens)
	{
		tok = tokens->content;
		if (tok->type != TOKEN_WORD)
			return (false);
		if (ft_strchr(tok->data, '$') != NULL)
			return (false);
		tokens = tokens->prev;
	}
	return (true);
}

static t_list	*locate_eq(t_list *tokens)
{
	t_token	*tok;

	if (tokens == NULL)
		return (NULL);
	while (tokens)
	{
		tok = tokens->content;
		if (tok == NULL)
			return (NULL);
		if (ft_strchr(tok->data, '=') != NULL)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

bool	is_assignment_statement(t_list *tokens)
{
	t_list	*eq;
	t_list	*et;

	et = get_enhanced_tokens(tokens, "=");
	eq = locate_eq(et);
	if (eq == NULL)
		return (ft_lstclear(&et, free_token), false);
	if (key_validation(eq) == false)
		return (ft_lstclear(&et, free_token), false);
	return (ft_lstclear(&et, free_token), true);
}
