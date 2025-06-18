/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 03:15:50 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/17 03:19:49 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

t_list *get_filename(t_list **tokens)
{
	t_list *filename;
	t_list *token_node;
	t_token *token;

	filename = NULL;
	token_node = NULL;
	token = NULL;
	if (tokens == NULL)
		return (NULL);
	skip_front_spaces(tokens);
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->type != TOKEN_WORD
			&& token->type != TOKEN_DOUBLE_QUOTE_WORD
			&& token->type != TOKEN_SINGLE_QUOTE_WORD)
			break;
		token_node = create_token_node(token->type, token->data);
		ft_lstadd_back(&filename, token_node);
		*tokens = (*tokens)->next;
	}
	return (filename);
}
