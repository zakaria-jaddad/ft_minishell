/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:19:14 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 00:29:51 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/ast.h"

t_list	*get_command(t_list **tokens)
{
	t_list	*commands;
	t_list	*command_node;
	t_token	*token;

	if (tokens == NULL)
		return (NULL);
	commands = NULL;
	command_node = NULL;
	skip_front_spaces(tokens);
	while ((*tokens))
	{
		token = (*tokens)->content;
		if (token->type != TOKEN_WORD && token->type != TOKEN_DOUBLE_QUOTE_WORD
			&& token->type != TOKEN_SINGLE_QUOTE_WORD)
			break ;
		command_node = create_token_node(token->type, token->data);
		if (command_node == NULL)
			return (ft_lstclear(&commands, free_token), NULL);
		ft_lstadd_back(&commands, command_node);
		(*tokens) = (*tokens)->next;
	}
	return (commands);
}

t_list	*get_arguments(t_list **tokens)
{
	t_list	*arguments;
	t_list	*argument_node;
	t_token	*token;

	if (tokens == NULL)
		return (NULL);
	arguments = NULL;
	token = NULL;
	argument_node = NULL;
	skip_front_spaces(tokens);
	while ((*tokens))
	{
		token = (*tokens)->content;
		if (is_token_special(token) == true)
			break ;
		argument_node = create_token_node(token->type, token->data);
		if (argument_node == NULL)
			return (ft_lstclear(&arguments, free_token), NULL);
		ft_lstadd_back(&arguments, argument_node);
		(*tokens) = (*tokens)->next;
	}
	return (arguments);
}

t_cmd	*ast_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->content = NULL;
	cmd->left = NULL;
	cmd->right = NULL;
	return (cmd);
}

void	tokens_clean_up(t_list **tokens)
{
	if (tokens == NULL || *tokens == NULL)
		return ;
	remove_front_spaces(tokens);
	remove_back_spaces(tokens);
	while (is_wrapped_by_single_paren_pair(*tokens))
		remove_per(tokens);
}

bool	is_node_redirection(t_node_type type)
{
	return (type == NODE_IN_REDIR || type == NODE_OUT_REDIR
		|| type == NODE_HEREDOC || type == NODE_APPEND_REDIR);
}
