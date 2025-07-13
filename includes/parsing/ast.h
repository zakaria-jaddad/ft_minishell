/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:06:52 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 00:26:09 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

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

t_list				*get_command(t_list **tokens);
t_list				*get_arguments(t_list **tokens);
t_cmd				*ast_new(void);
void				tokens_clean_up(t_list **tokens);
bool				is_node_redirection(t_node_type type);

#endif // AST_H
