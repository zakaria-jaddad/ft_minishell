/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/21 15:50:35 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing/parsing.h"
#include <stdio.h>

t_cmd	*parse_cmd(char *line, t_list *env_lst)
{
	t_list	*tokens;
        t_cmd   *cmd;

	(void)env_lst;
        cmd = NULL;
	tokens = get_tokens(line);
	if (tokens == NULL)
		return (NULL);

        // syntax_check() NOTE IMPLEMENTED
        if (syntax_check(&tokens) == false)
                return (ft_lstclear(&tokens, free_token), NULL);
        pre_ast(&tokens);
        cmd = ast(&tokens);
        if (cmd == NULL)
                return (ft_lstclear(&tokens, free_token), NULL);
	return (cmd);
}
