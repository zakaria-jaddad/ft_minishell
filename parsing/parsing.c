/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/08 19:19:48 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <stdlib.h>

void	print_tokens(t_list *tokens)
{
	t_token	*token;

	for (t_list *tmp = tokens; tmp != NULL; tmp = tmp->next)
	{
		token = (t_token *)tmp->content;
		fprintf(stdout, "data: \"%s\" %s\n", token->data,
			get_token_type(token->type));
	}
	printf("\n");
}

t_cmd	*parsing(char *line, t_list *env_lst)
{
	t_list	*tokens;

	(void)env_lst;
	tokens = get_tokens(line);
	print_tokens(tokens);
	if (tokens == NULL)
		return (NULL);
	ft_lstclear(&tokens, free_token);
        exit(0);
	return ((t_cmd *)tokens);
}
