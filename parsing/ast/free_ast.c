/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 01:58:10 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 00:29:35 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/ast.h"

void	free_cmd_redir(t_cmd_redir *redir)
{
	if (redir == NULL)
		return ;
	ft_lstclear(&redir->filename, free_token);
	free(redir);
}

void	free_cmd_simple(t_cmd_simple *simple_cmd)
{
	if (simple_cmd == NULL)
		return ;
	ft_lstclear(&simple_cmd->command, free_token);
	ft_lstclear(&simple_cmd->arguments, free_token);
	free(simple_cmd);
}

void	free_ast(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	free_ast(cmd->left);
	free_ast(cmd->right);
	if (is_node_redirection(cmd->type) == true)
		free_cmd_redir(cmd->content);
	else if (cmd->type == NODE_COMMAND)
		free_cmd_simple(cmd->content);
	free(cmd);
}
