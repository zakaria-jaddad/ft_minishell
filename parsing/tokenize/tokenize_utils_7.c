/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:40:28 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 02:05:29 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing/tokenize.h"

t_list	*get_tokenizd_word(t_list **tokens)
{
	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	return (get_filename(tokens));
}

void	invalid_quote(char *quote_type, char *token_data)
{
	ft_fprintf(STDERR_FILENO, SYNTAX_E, quote_type);
	status_x(258, true);
	token_data = (free(token_data), NULL);
}
