/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:40:28 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/24 09:40:41 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/tokenize.h"

t_list	*get_tokenizd_word(t_list **tokens)
{
	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	return (get_filename(tokens));
}
