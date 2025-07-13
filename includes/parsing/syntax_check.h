/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:35:24 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:35:25 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_CHECK_H
# define SYNTAX_CHECK_H

# include "../../libft/libft.h"
# include "tokenize.h"

# define SE "minishell: syntax error\n"
# define CLOSE_PER_SE "minishell: syntax error near unexpected token `)'\n"
# define OPEN_PER_SE "minishell: syntax error near unexpected token `('\n"
# define SYNTAX_E "minishell: syntax error near unexpected token `%s'\n"
# define PIPE_SE "minishell: syntax error near unexpected token `|'\n"

t_list	*get_subshell(t_list **t);
char	*get_td_from_tt(t_token_type t);
char	*get_redir_type(t_token *tok);
bool	is_logical_op(t_token_type type);
bool	is_type_word(t_token_type type);
bool	is_type_redirection(t_token_type type);
bool	check_redir(t_list *tokens);
bool	check_pipe(t_list *tokens);
bool	check_logical_operator(t_list *tokens);

#endif // !SYNTAX_CHECK_H
