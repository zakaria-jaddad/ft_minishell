/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_assignment_statement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:50:18 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/17 07:28:32 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

static int	ft_isalnum(int c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || (c >= '0'
			&& c <= '9') || c == '=')
		return (1);
	return (0);
}

static bool	is_alpha_numeric(char *str)
{
	while (*str)
	{
		if (ft_isalnum(*str) == false)
			return (false);
		str++;
	}
	return (true);
}

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
		if (is_alpha_numeric(tok->data) == false)
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
