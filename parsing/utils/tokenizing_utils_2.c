/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:41:23 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/08 16:58:12 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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
	return ("TOKEN_WORD");
}

/*
 * @brief append data to token data
 */
void	append_str(char **token_data, char *new_data)
{
	char	*tmp;

	if (token_data == NULL)
		return ;
	if (new_data == NULL)
		return ;
	tmp = *token_data;
	*token_data = ft_strjoin(tmp, new_data);
	if (*token_data == NULL)
		return ;
	tmp = (free(tmp), NULL);
}

/*
 * @brief append data to last token data
 */
void	append_last_toke_data(t_list **tokens, char *new_data)
{
	t_list	*last_token;

	if (tokens == NULL || *tokens == NULL)
		return ;
	last_token = ft_lstlast(*tokens);
	if (last_token == NULL)
		return ;
	append_str(&((t_token *)(last_token->content))->data, new_data);
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
