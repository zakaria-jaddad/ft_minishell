/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_enhanced_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:51:14 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:00:52 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"
#include <stdio.h>

t_list	*create_tokens(t_list *data_lst, t_token_type tokens_type)
{
	t_list	*new_tokens;
	t_list	*token_node;

	new_tokens = NULL;
	if (data_lst == NULL)
		return (NULL);
	while (data_lst && data_lst->content)
	{
		token_node = create_token_node(tokens_type, data_lst->content);
		if (token_node == NULL)
			return (ft_lstclear(&new_tokens, free_token), NULL);
		ft_lstadd_back(&new_tokens, token_node);
		data_lst = data_lst->next;
	}
	return (new_tokens);
}

t_list	*get_created_tokens(t_token *tok, char *delim)
{
	t_list	*split_token_data;
	t_list	*new_tokens;

	new_tokens = NULL;
	if (tok->type != TOKEN_WHITE_SPACE)
	{
		split_token_data = ft_split_pro(tok->data, delim);
		if (split_token_data == NULL)
		{
			return (NULL);
		}
		new_tokens = create_tokens(split_token_data, tok->type);
		ft_lstclear(&split_token_data, free);
	}
	else
		new_tokens = create_token_node(TOKEN_WHITE_SPACE, " ");
	return (new_tokens);
}

t_list	*get_enhanced_tokens(t_list *tokens, char *delim)
{
	t_list	*enhanced_tokens;
	t_list	*new_tokens;
	t_token	*tok;

	enhanced_tokens = NULL;
	while (tokens)
	{
		tok = tokens->content;
		if (tok->data != NULL && *tok->data == 0)
			new_tokens = create_token_node(tok->type, "");
		else
		{
			new_tokens = get_created_tokens(tok, delim);
			if (new_tokens == NULL)
				ft_lstclear(&enhanced_tokens, free_token);
		}
		if (new_tokens == NULL)
			return (ft_lstclear(&enhanced_tokens, free_token), NULL);
		ft_lstadd_back(&enhanced_tokens, new_tokens);
		tokens = tokens->next;
	}
	return (enhanced_tokens);
}
