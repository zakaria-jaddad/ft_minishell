/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/07 16:58:01 by zajaddad         ###   ########.fr       */
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
		fprintf(stderr, "data: \"%s\" %s ------> ", token->data,
			get_token_type(token->type));
		fflush(stdout);
	}
	printf("\n");
}

t_cmd	*parsing(char *line, t_list *env_lst)
{
	t_list	*tokens;

	(void)env_lst;
	tokens = get_tokens(line);
	print_tokens(tokens);
        free_tokens(&tokens);
	if (tokens == NULL)
		return (NULL);
	tokens = (free_tokens(&tokens), NULL);
	return ((t_cmd *)tokens);
}
