/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:11:49 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 00:21:58 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/ast.h"

t_cmd_redir	*create_redir(t_list **redir_start)
{
	t_list		*filename;
	t_cmd_redir	*cmd_redir;

	if (redir_start == NULL || *redir_start == NULL)
		return (NULL);
	*redir_start = (*redir_start)->next;
	filename = get_filename(redir_start);
	if (filename == NULL)
		return (NULL);
	cmd_redir = malloc(sizeof(t_cmd_redir));
	if (cmd_redir == NULL)
		return (ft_lstclear(&filename, free_token), NULL);
	cmd_redir->filename = filename;
	return (cmd_redir);
}

t_cmd_simple	*create_simple_cmd(t_list *cmd_start)
{
	t_cmd_simple	*cmd_simple;

	if (cmd_start == NULL)
		return (NULL);
	cmd_simple = malloc((sizeof(t_cmd_simple)));
	if (cmd_simple == NULL)
		return (NULL);
	cmd_simple->command = get_command(&cmd_start);
	if (cmd_simple == NULL)
		return (NULL);
	cmd_simple->arguments = get_arguments(&cmd_start);
	return (cmd_simple);
}

t_cmd	*parse_exec(t_list *tokens)
{
	t_cmd	*exec;

	exec = ast_new();
	if (exec == NULL)
		return (NULL);
	exec->type = NODE_COMMAND;
	exec->content = create_simple_cmd(tokens);
	if (exec->content == NULL)
		return (NULL);
	return (exec);
}

void	*handle_ast_redirectin(t_cmd *cmd_root, t_list *root, t_list **tokens)
{
	t_list	*redir_start;
	t_list	*right;
	t_list	*left;

	redir_start = root;
	cmd_root->type = (t_node_type)((t_token *)root->content)->type;
	cmd_root->content = create_redir(&redir_start);
	if (cmd_root->content == NULL)
		return (NULL);
	right = dup_tokens(redir_start, ft_lstlast(root), true);
	left = dup_tokens(*tokens, root, false);
	cmd_root->right = ast(&right);
	cmd_root->left = ast(&left);
	ft_lstclear(&right, free_token);
	ft_lstclear(&left, free_token);
	return (cmd_root);
}

t_cmd	*ast(t_list **tokens)
{
	t_cmd	*cmd_root;
	t_list	*root;
	t_list	*right;
	t_list	*left;

	(void)!(right = left = NULL);
	tokens_clean_up(tokens);
	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	root = get_root(*tokens);
	if (root == NULL)
		return (parse_exec(*tokens));
	cmd_root = ast_new();
	if (cmd_root == NULL)
		return (NULL);
	if (is_redirection(root->content) == true)
		return (handle_ast_redirectin(cmd_root, root, tokens));
	cmd_root->type = (t_node_type)((t_token *)root->content)->type;
	right = dup_tokens(root->next, ft_lstlast(root), true);
	left = dup_tokens(*tokens, root, false);
	cmd_root->right = ast(&right);
	cmd_root->left = ast(&left);
	ft_lstclear(&right, free_token);
	ft_lstclear(&left, free_token);
	return (cmd_root);
}
