/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_ast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:13:13 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:23:53 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRE_AST_H
# define PRE_AST_H

# include "../../libft/libft.h"
# include "tokenize.h"
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>

void		*pre_ast(t_list **tokens, t_list *envs);
void		enhance_redirection(t_list **redir_tokens, t_list **tokens);
char		*handle_heredoc(t_list *tokens, t_list *env_list);
uintptr_t	open_and_read_urandom(void);
char		*get_address(void *var);
char		*expand_arr(char **arr, t_list *envs);
int			count_allocate(char *str);

#endif // !PRE_AST_H
