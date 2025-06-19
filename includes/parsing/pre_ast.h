/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_ast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:13:13 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/19 08:17:10 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRE_AST_H
# define PRE_AST_H

# include "tokenize.h"
# include <stdbool.h>

void				pre_ast(t_list **tokens);
void				enhance_redirection(t_list **redir_tokens, t_list **tokens);

#endif // !PRE_AST_H
