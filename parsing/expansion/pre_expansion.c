/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:48:11 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/10 22:26:20 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"
#include <stdio.h>
#include <stdlib.h>

static void	wildcard_pre_expansion(t_list **tokens)
{
	t_list	*et;
	t_list	*prev;
	t_token	*tok;
	t_list	*head;

	if (tokens == NULL || *tokens == NULL)
		return ;
	et = get_enhanced_tokens(*tokens, "=*");
	head = et;
	while (et)
	{
		tok = et->content;
		if (ft_strcmp(tok->data, "*") == 0)
		{
			prev = et->prev;
			if (prev != NULL && ft_strcmp(((t_token *)(prev->content))->data,
					"=") == 0)
				tok->type = TOKEN_DOUBLE_QUOTE_WORD;
		}
		et = et->next;
	}
	ft_lstclear(tokens, free_token);
	*tokens = head;
}

static void	*split_pre_expansion_escapint_norms_v2(t_list **new_tokens,
		t_list **wordt)
{
	t_list	*argt;

	argt = create_enhanced_tokens(*wordt, false);
	if (argt == NULL)
		return (ft_lstclear(new_tokens, free_token), ft_lstclear(wordt,
				free_token), NULL);
	ft_lstadd_back(new_tokens, argt);
	if (append_tokens(new_tokens, TOKEN_WHITE_SPACE, " ") == NULL)
		return (ft_lstclear(new_tokens, free_token), ft_lstclear(wordt,
				free_token), ft_lstclear(&argt, free_token), NULL);
	ft_lstclear(wordt, free_token);
	return (NOTNULL);
}

static void	*split_pre_expansion_escapint_norms_v1(t_list **new_tokens,
		t_list **wordt)
{
	t_list	*argt;

	argt = create_enhanced_tokens(*wordt, true);
	if (argt == NULL)
		return (ft_lstclear(new_tokens, free_token), ft_lstclear(wordt,
				free_token), NULL);
	ft_lstadd_back(new_tokens, argt);
	if (append_tokens(new_tokens, TOKEN_WHITE_SPACE, " ") == NULL)
		return (ft_lstclear(new_tokens, free_token), ft_lstclear(wordt,
				free_token), ft_lstclear(&argt, free_token), NULL);
	ft_lstclear(wordt, free_token);
	return (NOTNULL);
}

static void	split_pre_expansion(t_list **tokens)
{
	t_list	*tmp;
	t_list	*new_tokens;
	t_list	*wordt;

	if (tokens == NULL || *tokens == NULL)
		return ;
	(void)!(tmp = *tokens, new_tokens = NULL, wordt = NULL);
	while (tmp)
	{
		if (((t_token *)tmp->content)->type != TOKEN_WHITE_SPACE)
		{
			wordt = get_tokenizd_word(&tmp);
			if (wordt == NULL)
				return (ft_lstclear(&new_tokens, free_token));
			if (is_assignment_statement(wordt) == true)
			{
				if (!split_pre_expansion_escapint_norms_v1(&new_tokens, &wordt))
					return ;
				continue ;
			}
			if (!split_pre_expansion_escapint_norms_v2(&new_tokens, &wordt))
				return ;
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
	(void)!(ft_lstclear(tokens, free_token), *tokens = new_tokens);
}

void	pre_expansion(t_list *command, t_list *cmdt, t_list **tokens)
{

	if (command != NULL && check_cmdt(cmdt) == false)
		split_pre_expansion(tokens);
	wildcard_pre_expansion(tokens);
}
