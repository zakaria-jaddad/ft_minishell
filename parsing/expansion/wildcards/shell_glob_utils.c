/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_glob_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 07:55:16 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/24 09:48:22 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing/expansion.h"

t_list	*get_word(t_list *tokens)
{
	if (tokens == NULL)
		return (NULL);
	while (tokens && is_word(tokens->content) == true)
	{
		if (tokens->prev == NULL)
			break ;
		tokens = tokens->prev;
	}
	return (get_filename(&tokens));
}

bool	is_valid_word(t_list *tokens_word)
{
	t_token	*token;

	while (tokens_word && tokens_word->content)
	{
		token = tokens_word->content;
		if (check_token_type(token, TOKEN_WORD) == true)
		{
			tokens_word = tokens_word->next;
			continue ;
		}
		if (ft_strcmp(token->data, "*") == 0)
			return (false);
		tokens_word = tokens_word->next;
	}
	return (true);
}

bool	is_valid_wildcard(t_list *current_token_node)
{
	t_token	*current_token;

	if (current_token_node == NULL)
		return (false);
	current_token = current_token_node->content;
	if (check_token_type(current_token, TOKEN_WORD)
		&& ft_strcmp(current_token->data, "*") == 0)
		return (true);
	if (check_token_type(current_token, TOKEN_DOUBLE_QUOTE_WORD)
		|| check_token_type(current_token, TOKEN_SINGLE_QUOTE_WORD))
		return (false);
	return (false);
}

t_list	*create_tokenized_matches(t_list *filename)
{
	t_list	*token_node;
	t_list	*tokenized_filenames;

	if (filename == NULL)
		return (NULL);
	tokenized_filenames = NULL;
	while (filename)
	{
		token_node = create_token_node(TOKEN_WORD, filename->content);
		if (token_node == NULL)
			return (ft_lstclear(&tokenized_filenames, free_token), NULL);
		ft_lstadd_back(&tokenized_filenames, token_node);
		if (append_tokens(&tokenized_filenames, TOKEN_WHITE_SPACE, " ") == NULL)
			return (ft_lstclear(&tokenized_filenames, free_token), NULL);
		filename = filename->next;
	}
	return (tokenized_filenames);
}
