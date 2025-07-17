/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 06:45:42 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/17 23:20:49 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

static bool	is_ws_found(char *s)
{
	return (ft_strcmp(s, " ") == 0 || ft_strcmp(s, "\t") == 0);
}

bool	gwten(t_list *wordt_node, t_list **sptw_head, t_list **wordt)
{
	if (wordt_node == NULL)
		return (ft_lstclear(sptw_head, free), ft_lstclear(wordt, free_token),
			false);
	return (true);
}

void	i_(char *token_data, t_list **sptw, t_list **sptw_head, t_list **wordt)
{
	*sptw = ft_split_pro_max(token_data, " \t\n");
	(void)!(*sptw_head = *sptw, *wordt = NULL);
}

t_list	*get_word_tokens(t_token *token)
{
	t_list	*sptw;
	t_list	*wordt;
	t_list	*wordt_node;
	t_list	*sptw_head;

	(void)!(i_(token->data, &sptw, &sptw_head, &wordt), 0);
	while (sptw && sptw->content)
	{
		if (is_ws_found(sptw->content))
			wordt_node = create_token_node(TOKEN_WHITE_SPACE, " ");
		else
			wordt_node = create_token_node(TOKEN_WORD, sptw->content);
		if (gwten(wordt_node, &sptw_head, &wordt) == false)
			return (NULL);
		(void)!(sptw = sptw->next, ft_lstadd_back(&wordt, wordt_node), 0);
	}
	return (ft_lstclear(&sptw_head, free), wordt);
}
