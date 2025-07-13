/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enhance_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:57:24 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:11:07 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/pre_ast.h"

static void	skip_redirections(t_list **tokens)
{
	t_token	*token;
	t_list	*filename;

	if (tokens == NULL || *tokens == NULL)
		return ;
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token == NULL || is_redirection(token) == false)
			return ;
		*tokens = (*tokens)->next;
		skip_front_spaces(tokens);
		filename = get_filename(tokens);
		if (filename == NULL)
			return ;
		ft_lstclear(&filename, free_token);
		if (*tokens == NULL)
			return ;
		skip_front_spaces(tokens);
	}
}

static void	move_redirection_after(t_list *cmd_node, t_list **redir_node)
{
	t_list	*redir_prev;
	t_list	*cmd_tail;

	if (cmd_node == NULL || redir_node == NULL || *redir_node == NULL)
		return ;
	cmd_node = dup_and_remove_simple_tokens(cmd_node);
	if (cmd_node == NULL)
		return ;
	redir_prev = (*redir_node)->prev;
	if (redir_prev != NULL)
	{
		cmd_tail = ft_lstlast(cmd_node);
		redir_prev->next = cmd_node;
		cmd_node->prev = redir_prev;
		cmd_tail->next = *redir_node;
		(*redir_node)->prev = cmd_tail;
		return ;
	}
	ft_lstadd_back(&cmd_node, (*redir_node));
	*redir_node = cmd_node;
}

void	enhance_redirection(t_list **redir_tokens, t_list **tokens)
{
	t_list	*cmd_node;
	t_list	*redir_start;

	if (tokens == NULL || *tokens == NULL || redir_tokens == NULL
		|| *redir_tokens == NULL)
		return ;
	cmd_node = (*redir_tokens);
	redir_start = (*redir_tokens);
	skip_redirections(&cmd_node);
	if (cmd_node != NULL && is_word(cmd_node->content))
	{
		move_redirection_after(cmd_node, redir_tokens);
		(*tokens) = ft_lstfirst(redir_start);
		*redir_tokens = redir_start;
		return ;
	}
	(*redir_tokens) = cmd_node;
}
