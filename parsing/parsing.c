/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 16:24:59 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_cmd	*parsing(char *line, t_list *env_lst)
{
	t_list	*tokens;
	t_list	*matches;

	(void)env_lst;
	tokens = get_tokens(line);
	if (tokens == NULL)
		return (NULL);
	matches = expand_wildcard(((t_token *)tokens->content)->data);
	print_tokens(tokens);
	ft_lstclear(&tokens, free_token);
	for (t_list *tmp = matches; tmp != NULL; tmp = tmp->next)
	{
		printf("matched node: %10s\n", (char *)tmp->content);
	}
	ft_lstclear(&matches, free);
	ft_lstclear(&env_lst, free_env);
	exit(0);
	return ((t_cmd *)tokens);
}
