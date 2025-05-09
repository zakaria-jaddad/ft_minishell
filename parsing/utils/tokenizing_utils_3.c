/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:07:45 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/09 15:44:20 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
 * @brief Checks if last token, it's last character is equal
 * @return: true if equal found, false if not found
 */
bool	check_equal_in_last_token(t_list *tokens)
{
	t_token	*current_token;
	t_list	*lstlast_token;

	if (tokens == NULL)
		return (false);
	lstlast_token = ft_lstlast(tokens);
	if (lstlast_token == NULL)
		return (false);
	current_token = lstlast_token->content;
	if (current_token->data == NULL || *(current_token->data) == 0)
		return (false);
	if ((current_token->data)[ft_strlen(current_token->data) - 1] == '=')
		return (true);
	return (false);
}

/*
 * @brief Checks if last token has a type of:
 *      -> TOKEN_WHITE_SPACE
 * @return: true if token type equal tokens false if not
 */
bool	is_last_token_type_space(t_list *tokens)
{
	t_list	*last_token_node;
	t_token	*token;

	last_token_node = ft_lstlast(tokens);
	if (last_token_node == NULL)
		return (NULL);
	token = last_token_node->content;
	if (token == NULL)
		return (NULL);
	if (token->type == TOKEN_WHITE_SPACE)
		return (true);
	return (false);
}

void	print_split(t_list *line_lst)
{
	if (line_lst == NULL)
		printf("(null)");
	while (line_lst)
	{
		ft_fprintf(STDOUT_FILENO, "\"%s\" --- > ", (char *)line_lst->content);
		line_lst = line_lst->next;
	}
	ft_fprintf(STDOUT_FILENO, "\n");
}
