/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:58:48 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/19 00:05:09 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	is_valid_per(t_list *tokens)
{
	int		depth;
	t_token	*token;

	(void)!(token = NULL, depth = 0);
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == TOKEN_PAR_OPEN)
			depth++;
		else if (token->type == TOKEN_PAR_CLOSE)
		{
			depth--;
			if (depth < 0)
				return (ft_fprintf(STDERR_FILENO,
						"bash: syntax error near unexpected token `%s\'\n",
						token->data), false);
		}
		tokens = tokens->next;
	}
	if (depth != 0)
		return (ft_fprintf(STDERR_FILENO,
				"bash: syntax error near unexpected token `(\'\n"), false);
	return (true);
}

bool	syntax_check(t_list **tokens)
{
	if (tokens == NULL || *tokens == NULL)
		return (false);
	if (is_valid_per(*tokens) == false)
		return (false);
	return (true);
}
