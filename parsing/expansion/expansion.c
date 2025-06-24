/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:44:31 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/24 11:44:09 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

t_list	*expand_me(t_list *tokens, t_list *env)
{
	t_list	*enhanced_tokens;
        t_list *tmp;

	enhanced_tokens = get_enhanced_tokens(tokens, "$*?");
	if (enhanced_tokens == NULL)
		return (NULL);
	expand_dollar(&enhanced_tokens, env);
	tmp = expand_wildcard(enhanced_tokens);
	if (tmp == NULL)
		return (enhanced_tokens);
	ft_lstclear(&enhanced_tokens, free_token);
	return (tmp);
}
