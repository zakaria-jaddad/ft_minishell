/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:44:31 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/04 00:37:22 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

t_list	*get_word_tokens(t_token *token)
{
	t_list	*split_tokenized_word;
	t_list	*word_tokens;

	if (token == NULL)
		return (NULL);
	split_tokenized_word = ft_split_pro_max(token->data, " \t\n");
	if (split_tokenized_word == NULL)
		return (NULL);
	word_tokens = create_tokens(split_tokenized_word, token->type);
	if (word_tokens == NULL)
		return (ft_lstclear(&split_tokenized_word, free), NULL);
	ft_lstclear(&split_tokenized_word, free);
	return (word_tokens);
}

void	handle_space_string(t_list **tokens, t_list **tokens_tmp)
{
	t_list	*node_to_del;

	if (tokens == NULL || tokens_tmp == NULL)
		return ;
	if (*tokens == NULL || *tokens_tmp == NULL)
		return ;
	node_to_del = *tokens_tmp;
	*tokens_tmp = (*tokens_tmp)->next;
	ft_lst_rm_one(tokens, node_to_del, free_token);
}

void	insert_split_tokens(t_list **tokens, t_list **tokens_tmp,
		t_list *word_tokens)
{
	t_list	*node_to_del;
	t_list	*prev;
	t_list	*next;
	t_list	*word_tail;

	if (tokens == NULL || tokens_tmp == NULL || *tokens_tmp == NULL
		|| word_tokens == NULL)
		return ;
	node_to_del = *tokens_tmp;
	prev = (*tokens_tmp)->prev;
	next = (*tokens_tmp)->next;
	*tokens_tmp = (*tokens_tmp)->next;
	ft_lst_rm_one(tokens, node_to_del, free_token);
	word_tail = ft_lstlast(word_tokens);
	if (prev == NULL)
		*tokens = word_tokens;
	else
		(void)!(prev->next = word_tokens, word_tokens->prev = prev);
	if (next)
		(void)!(word_tail->next = next, next->prev = word_tail);
}

void	split_enhanced_tokens(t_list **tokens)
{
	t_list	*tokens_tmp;
	t_token	*tok;
	t_list	*word_tokens;

	tokens_tmp = *tokens;
	while (tokens_tmp)
	{
		tok = tokens_tmp->content;
		if (is_word_and_space_found(tok))
		{
			if (count_spaces(tok->data) != (int) ft_strlen(tok->data))
			{
				word_tokens = get_word_tokens(tok);
				if (word_tokens == NULL)
					return ;
				insert_split_tokens(tokens, &tokens_tmp, word_tokens);
			}
			else
				handle_space_string(tokens, &tokens_tmp);
			continue ;
		}
		tokens_tmp = tokens_tmp->next;
	}
}

t_list	*expand(t_list *tokens, t_list *env)
{
	t_list	*enhanced_tokens;
	t_list	*tmp;

	enhanced_tokens = get_enhanced_tokens(tokens, "$");
	if (enhanced_tokens == NULL)
		return (NULL);
	expand_dollar(&enhanced_tokens, env);
	tmp = expand_wildcard(enhanced_tokens);
	if (tmp == NULL)
	{
		if (enhanced_tokens == NULL)
			return (NULL);
		split_enhanced_tokens(&enhanced_tokens);
		return (enhanced_tokens);
	}
	ft_lstclear(&enhanced_tokens, free_token);
	return (tmp);
}
