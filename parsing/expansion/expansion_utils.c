/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:50:30 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 02:34:20 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"
#include <stdio.h>

bool	is_word_and_space_found(t_token *token)
{
	return (check_token_type(token, TOKEN_WORD) == true
		&& ft_strpbrk(token->data, " \t") != NULL);
}

int	ist(t_list **tokens, t_list **tokens_tmp, t_list *wordt)
{
	t_list	*node_to_del;
	t_list	*prev;
	t_list	*next;
	t_list	*word_tail;

	if (tokens == NULL || tokens_tmp == NULL || *tokens_tmp == NULL
		|| wordt == NULL)
		return (0);
	node_to_del = *tokens_tmp;
	prev = (*tokens_tmp)->prev;
	next = (*tokens_tmp)->next;
	*tokens_tmp = (*tokens_tmp)->next;
	ft_lst_rm_one(tokens, node_to_del, free_token);
	word_tail = ft_lstlast(wordt);
	if (prev == NULL)
		*tokens = wordt;
	else
		(void)!(prev->next = wordt, wordt->prev = prev);
	if (next)
		(void)!(word_tail->next = next, next->prev = word_tail);
	return (0);
}

void	del_token(t_list **tokens_tmp, t_list **tokens)
{
	t_list	*node_to_del;

	node_to_del = *tokens_tmp;
	*tokens_tmp = (*tokens_tmp)->next;
	ft_lst_rm_one(tokens, node_to_del, free_token);
}
