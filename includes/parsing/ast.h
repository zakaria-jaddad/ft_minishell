/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:06:52 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/04 03:00:02 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST
# define AST

# include "../../libft/libft.h"
# include "tokenize.h"
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

typedef enum e_node_type
{
	NODE_PIPE = TOKEN_PIPE,
	NODE_IN_REDIR = TOKEN_IN_REDIR,
	NODE_OUT_REDIR = TOKEN_OUT_REDIR,
	NODE_HEREDOC = TOKEN_HEREDOC,
	NODE_APPEND_REDIR = TOKEN_APPEND_REDIR,
	NODE_IF_OR = TOKEN_IF_OR,
	NODE_IF_AND = TOKEN_IF_AND,
	NODE_COMMAND = 100,
	NODE_INVALID = 200
}					t_node_type;

typedef struct s_cmd_simple
{
	t_list			*command;
	t_list			*arguments;
}					t_cmd_simple;

typedef struct s_cmd_redir
{
	t_list			*filename;
}					t_cmd_redir;

typedef struct s_cmd
{
	t_node_type		type;
	struct s_cmd	*left;
	struct s_cmd	*right;
	void			*content;
}					t_cmd;

t_list				*get_root(t_list *tokens);
t_cmd				*ast(t_list **tokens);
void				free_ast(t_cmd *cmd);

static inline void	print_depth(int depth)
{
	for (int i = 0; i < depth; i++)
		ft_fprintf(STDOUT_FILENO, "    ");
}

static inline bool	is_node_redirection(t_node_type type)
{
	return (type == NODE_IN_REDIR || type == NODE_OUT_REDIR
		|| type == NODE_HEREDOC || type == NODE_APPEND_REDIR);
}

static inline char	*get_node_type(t_node_type type)
{
	if (type == NODE_PIPE)
		return ("NODE_PIPE");
	if (type == NODE_IN_REDIR)
		return ("NODE_IN_REDIR");
	if (type == NODE_OUT_REDIR)
		return ("NODE_OUT_REDIR");
	if (type == NODE_IF_AND)
		return ("NODE_IF_AND");
	if (type == NODE_IF_OR)
		return ("NODE_IF_OR");
	if (type == NODE_HEREDOC)
		return ("NODE_HEREDOC");
	if (type == NODE_APPEND_REDIR)
		return ("NODE_APPEND_REDIR");
	if (type == NODE_COMMAND)
		return ("NODE_COMMAND");
	return ("NODE_INVALID");
}

static inline void	print_cmd(t_cmd *root, int depth)
{
	t_cmd_redir		*redir;
	t_cmd_simple	*simple_command;

	if (root == NULL)
		return ;
	ft_fprintf(STDOUT_FILENO, "\n");
	print_depth(depth);
	// Print current node
	if (depth == 0)
		ft_fprintf(STDOUT_FILENO, "root   : ");
	else
		ft_fprintf(STDOUT_FILENO, "╰───   : ");
	ft_fprintf(STDOUT_FILENO, "type: %s\n", get_node_type(root->type));
	if (is_node_redirection(root->type) == true)
	{
		print_depth(depth + 3);
		ft_fprintf(STDOUT_FILENO, "filename huh : ");
		redir = (t_cmd_redir *)root->content;
		print_tokens(redir->filename);
		ft_fprintf(STDOUT_FILENO, ": ");
		print_tokens_data(redir->filename);
	}
	else if (root->type == NODE_COMMAND)
	{
		simple_command = (t_cmd_simple *)root->content;
		print_depth(depth + 3);
		ft_fprintf(STDOUT_FILENO, "command: ");
		print_tokens(simple_command->command);
		ft_fprintf(STDOUT_FILENO, ": ");
		print_tokens_data(simple_command->command);
		print_depth(depth + 3);
		ft_fprintf(STDOUT_FILENO, "arguments: ");
		print_tokens(simple_command->arguments);
		ft_fprintf(STDOUT_FILENO, ": ");
		print_tokens_data(simple_command->arguments);
		ft_fprintf(STDOUT_FILENO, "\n");
	}
	ft_fprintf(STDOUT_FILENO, "\n");
	print_cmd(root->left, depth + 1);
	print_cmd(root->right, depth + 1);
}

#endif // AST_H
