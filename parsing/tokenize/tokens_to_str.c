/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:06:00 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 02:06:02 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/tokenize.h"

char	*tokens_to_str(t_list *tokens)
{
	t_token	*token;
	char	*rv;
	char	*tmp;

	rv = NULL;
	while (tokens)
	{
		token = tokens->content;
		tmp = ft_strjoin(rv, token->data);
		free(rv);
		rv = tmp;
		tokens = tokens->next;
	}
	return (rv);
}
