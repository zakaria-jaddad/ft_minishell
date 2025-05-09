/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/09 15:30:52 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_cmd	*parsing(char *line, t_list *env_lst)
{
	t_list	*tokens;

	(void)env_lst;
	tokens = get_tokens(line);
	print_tokens(tokens);
	if (tokens == NULL)
		return (NULL);
	return ((t_cmd *)tokens);
}
