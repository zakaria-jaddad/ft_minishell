/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:48:02 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/16 01:51:48 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"


void remove_front_spaces(t_list **tokens)
{
    t_list  *curr;
    t_list  *next;
    t_token *token;

    if (!tokens || !*tokens)
        return;

    curr = *tokens;
    while (curr)
    {
        token = curr->content;
        if (token->type != TOKEN_WHITE_SPACE)
            break;

        next = curr->next;
        if (next)
            next->prev = NULL;

        ft_lst_rm_one(curr, free_token);  // free safely
        curr = next;
    }
    *tokens = curr;
}


void remove_back_spaces(t_list **tokens)
{
	t_token *token;
	t_list  *curr;
	t_list  *prev;

	if (!tokens || !*tokens)
		return;

	curr = ft_lstlast(*tokens);
	while (curr)
	{
		token = (t_token *)curr->content;
		if (token->type != TOKEN_WHITE_SPACE)
			break;

		prev = curr->prev;
		if (prev)
			prev->next = NULL;
		else
			*tokens = NULL;  // entire list was whitespace

		curr->prev = NULL;
		curr->next = NULL;
		ft_lstdelone(curr, free_token);

		curr = prev;
	}
}

