/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_enhanced_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:51:14 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/27 16:14:41 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

static int	count_spaces(char *s)
{
	int	spaces;

	spaces = 0;
	while (*s)
	{
		if (*s == ' ')
			spaces++;
		s++;
	}
	return (spaces);
}

static bool check_spaces(char *str)
{
	return (count_spaces(str) == (int) ft_strlen(str));
}

t_list	*create_tokens(t_list *data_lst, t_token_type tokens_type)
{
	t_list	*new_tokens;
	t_list	*token_node;

	new_tokens = NULL;
	if (data_lst == NULL)
		return (NULL);
	while (data_lst)
	{
		if (check_spaces(data_lst->content) == true)
			token_node = create_token_node(TOKEN_WHITE_SPACE, data_lst->content);
		else
			token_node = create_token_node(tokens_type, data_lst->content);
		if (token_node == NULL)
			return (ft_lstclear(&new_tokens, free_token), NULL);
		ft_lstadd_back(&new_tokens, token_node);
		data_lst = data_lst->next;
	}
	return (new_tokens);
}

t_list	*get_enhanced_tokens(t_list *tokens, char *delim)
{
	t_list	*enhanced_tokens;
	t_list	*new_tokens;
	t_token	*current_token;
	t_list	*split_token_data;

	enhanced_tokens = NULL;
	while (tokens)
	{
		current_token = tokens->content;
		if (current_token->data != NULL && *current_token->data == 0)
			new_tokens = create_token_node(current_token->type, "");
		else
		{
			split_token_data = ft_split_pro(current_token->data, delim);
			if (split_token_data == NULL)
				break ;
			new_tokens = create_tokens(split_token_data, current_token->type);
			ft_lstclear(&split_token_data, free);
		}
		if (new_tokens == NULL)
			ft_lstclear(&enhanced_tokens, free_token);
		ft_lstadd_back(&enhanced_tokens, new_tokens);
		tokens = tokens->next;
	}
	return (enhanced_tokens);
}
