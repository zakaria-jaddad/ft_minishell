/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:41:23 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:54:39 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/tokenize.h"

/*
 * @brief append data to token data
 */
void	append_str(char **current_data, char *to_append)
{
	char	*tmp;

	if (current_data == NULL || to_append == NULL)
		return ;
	tmp = ft_strjoin(*current_data, to_append);
	if (tmp == NULL)
		return ;
	free(*current_data);
	*current_data = tmp;
}

/*
 * @brief Creates a list node
 * @return: true if equal found, false if not found
 */
t_list	*get_token_node(t_list *line_lst)
{
	if (ft_strcmp(line_lst->content, ">>") == 0)
		return (create_token_node(TOKEN_APPEND_REDIR, line_lst->content));
	else if (ft_strcmp(line_lst->content, "<<") == 0)
		return (create_token_node(TOKEN_HEREDOC, line_lst->content));
	else if (ft_strcmp(line_lst->content, "<") == 0)
		return (create_token_node(TOKEN_IN_REDIR, line_lst->content));
	else if (ft_strcmp(line_lst->content, ">") == 0)
		return (create_token_node(TOKEN_OUT_REDIR, line_lst->content));
	else if (ft_strcmp(line_lst->content, "|") == 0)
		return (create_token_node(TOKEN_PIPE, line_lst->content));
	else if (ft_strcmp(line_lst->content, "(") == 0)
		return (create_token_node(TOKEN_PAR_OPEN, line_lst->content));
	else if (ft_strcmp(line_lst->content, ")") == 0)
		return (create_token_node(TOKEN_PAR_CLOSE, line_lst->content));
	else if (ft_strcmp(line_lst->content, "&&") == 0)
		return (create_token_node(TOKEN_IF_AND, line_lst->content));
	else if (ft_strcmp(line_lst->content, "||") == 0)
		return (create_token_node(TOKEN_IF_OR, line_lst->content));
	else if (ft_strcmp(line_lst->content, " ") == 0
		|| ft_strcmp(line_lst->content, "\t") == 0)
		return (create_token_node(TOKEN_WHITE_SPACE, line_lst->content));
	return (create_token_node(TOKEN_WORD, line_lst->content));
}
