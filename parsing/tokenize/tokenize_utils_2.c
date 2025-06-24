/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:41:23 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/20 04:27:30 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/tokenize.h"

/*
 * @return: returns a string of the given token
 */
char	*get_token_type(t_token_type token)
{
	if (token == TOKEN_PAR_OPEN)
		return ("TOKEN_PAR_OPEN");
	if (token == TOKEN_PAR_CLOSE)
		return ("TOKEN_PAR_CLOSE");
	if (token == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	if (token == TOKEN_IN_REDIR)
		return ("TOKEN_IN_REDIR");
	if (token == TOKEN_OUT_REDIR)
		return ("TOKEN_OUT_REDIR");
	if (token == TOKEN_IF_AND)
		return ("TOKEN_IF_AND");
	if (token == TOKEN_IF_OR)
		return ("TOKEN_IF_OR");
	if (token == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	if (token == TOKEN_APPEND_REDIR)
		return ("TOKEN_APPEND_REDIR");
	if (token == TOKEN_WHITE_SPACE)
		return ("TOKEN_WHITE_SPACE");
	if (token == TOKEN_DOUBLE_QUOTE_WORD)
		return ("TOKEN_DOUBLE_QUOTE_WORD");
	if (token == TOKEN_SINGLE_QUOTE_WORD)
		return ("TOKEN_SINGLE_QUOTE_WORD");
	if (token == TOKEN_COMMAND) // FIX: THERE IS NO TOKEN_COMMAND
		return ("TOKEN_COMMAND");
	return ("TOKEN_WORD");
}

/*
 * @brief append data to token data
 */
void append_str(char **current_data,  char *to_append)
{
    char *tmp;

    if (current_data == NULL || to_append == NULL)
        return;
    tmp = ft_strjoin(*current_data, to_append);
    if (tmp == NULL)
        return;
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
