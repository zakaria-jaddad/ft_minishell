/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:44:31 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/23 18:10:46 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

t_list	*expand_me(t_list *tokens, t_list *env)
{
	/* char	*pre_expansion_name; */
	/* t_list	*filenames; */
	/* t_list	*tokenized_filename; */
	/* t_token	*current_token; */
	/* t_list	*enhanced_tokens_head; */
	/* t_list	*current_word; */
	t_list	*enhanced_tokens;
	t_list	*tmp;

	enhanced_tokens = get_enhanced_tokens(tokens, "$*?");
	if (enhanced_tokens == NULL)
		return (NULL);
	tmp = expand_dollar(enhanced_tokens, env);
	if (tmp == NULL)
		return (ft_lstclear(&enhanced_tokens, free_token), NULL);
	enhanced_tokens = tmp;

	// Wildcard expanstion
	//
	/* enhanced_tokens = enhanced_tokens_head; */
	/* while (enhanced_tokens) */
	/* { */
	/* 	current_token = enhanced_tokens->content; */
	/* 	if (check_token_type(current_token, TOKEN_WORD) == true */
	/* 		&& ft_strcmp(current_token->data, "*") != 0) */
	/* 	{ */
	/* 		enhanced_tokens = enhanced_tokens->next; */
	/* 		continue ; */
	/* 	} */
	/* 	if (check_token_type(current_token, TOKEN_DOUBLE_QUOTE_WORD) == true */
	/* 		|| check_token_type(current_token, TOKEN_SINGLE_QUOTE_WORD) == true) */
	/* 	{ */
	/* 		enhanced_tokens = enhanced_tokens->next; */
	/* 		continue ; */
	/* 	} */
	/* 	current_word = get_word_start(enhanced_tokens); */
	/* 	if (current_word == NULL) */
	/* 		break ; */
	/* 	if (validate_word(current_word) == false) */
	/* 	{ */
	/* 		enhanced_tokens = enhanced_tokens->next; */
	/* 		continue ; */
	/* 	} */
	/* 	pre_expansion_name = get_pre_expanded_file_name(current_word); */
	/* 	if (pre_expansion_name == NULL) */
	/* 		return (ft_lstclear(&enhanced_tokens, free_token), NULL); */
	/* 	filenames = expand_wildcard(pre_expansion_name); */
	/* 	if (filenames == NULL) */
	/* 		return (ft_lstclear(&enhanced_tokens, free_token), NULL); */
	/* 	tokenized_filename = create_tokenized_filenames(filenames); */
	/* 	append_filenames(&enhanced_tokens, &current_word, tokenized_filename); */
	/* 	enhanced_tokens_head = ft_lstfirst(current_word); */
	/* 	if (enhanced_tokens != NULL) */
	/* 		enhanced_tokens = enhanced_tokens->next; */
	/* 	else */
	/* 		break ; */
	/* } */
	return (enhanced_tokens);
}
/**/
/* void	append_filenames(t_list **enhanced_tokens, t_list **tokens_word_start, */
/* 		t_list *tokenized_filenames) */
/* { */
/* 	t_list	*start; */
/* 	t_list	*end; */
/* 	t_list	*tmp; */
/* 	t_list	*curr; */
/* 	t_list	*last; */
/* 	start = NULL; */
/* 	end = NULL; */
/* 	if (!tokens_word_start || !*tokens_word_start || !tokenized_filenames) */
/* 		return ; */
/* 	curr = *tokens_word_start; */
/* 	start = curr->prev; */
/* 	while (curr && is_word(curr->content)) */
/* 		curr = curr->next; */
/* 	end = curr; */
/* 	curr = (start) ? start->next : *tokens_word_start; */
/* 	while (curr != end) */
/* 	{ */
/* 		tmp = curr->next; */
/* 		ft_lst_rm_one(curr, free_token); */
/* 		curr = tmp; */
/* 	} */
/* 	if (start) */
/* 	{ */
/* 		start->next = tokenized_filenames; */
/* 		tokenized_filenames->prev = start; */
/* 	} */
/* 	else */
/* 		*tokens_word_start = tokenized_filenames; */
/* 	*enhanced_tokens = ft_lstlast(tokenized_filenames); */
/* 	last = ft_lstlast(tokenized_filenames); */
/* 	last->next = end; */
/* 	if (end) */
/* 		end->prev = last; */
/* 	while ((*tokens_word_start)->prev) */
/* 		*tokens_word_start = (*tokens_word_start)->prev; */
/* } */
