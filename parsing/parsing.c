/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/19 00:05:38 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_cmd	*parse_cmd(char *line, t_list *env_lst)
{
	t_list	*tokens;
	t_cmd	*cmd;

	(void)env_lst;
	tokens = get_tokens(line);
	if (tokens == NULL)
		return (NULL);

        // syntax_check() NOTE IMPLEMENTED
        if (syntax_check(&tokens) == false)
                return (ft_lstclear(&tokens, free_token), NULL);
        pre_ast(&tokens);
        print_tokens_data(tokens);
	return ((t_cmd *)NULL);
}
