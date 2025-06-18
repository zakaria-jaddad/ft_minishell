/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:06:04 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/18 22:06:13 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	remove_es(t_list **tokens)
{
	t_list	*th;
	t_list	*tt;
	t_token	*token;
	int		lst_size;

	if (tokens == NULL)
		return ;
	(th = *tokens, lst_size = ft_lstsize(*tokens));
	while (th)
	{
		token = th->content;
		if ((token->type == TOKEN_DOUBLE_QUOTE_WORD
				|| token->type == TOKEN_SINGLE_QUOTE_WORD)
			&& token->data != NULL && *token->data == 0)
		{
			(tt = th, th = th->next, ft_lst_rm_one(tt, free_token));
			lst_size--;
			continue ;
		}
		if (th == NULL)
			return ;
		th = th->next;
	}
	if (lst_size == 0)
		*tokens = NULL;
}
