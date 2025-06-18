/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:37:13 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/18 21:30:38 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static void	*get_tokens_escaping_norms_1(t_list **line_lst,
		t_list *line_lst_head, t_list **tokens)
{
	t_list	*node;

	node = NULL;
	if (line_lst == NULL || *line_lst == NULL)
		return (NULL);
	if (tokens == NULL)
		return (NULL);
	if (ft_strcmp((*line_lst)->content, "\"") == 0)
		node = tokenize_quotes("\"", TOKEN_DOUBLE_QUOTE_WORD, line_lst);
	else
		node = tokenize_quotes("\'", TOKEN_SINGLE_QUOTE_WORD, line_lst);
	if (node == NULL)
		return (ft_lstclear(&line_lst_head, free), ft_lstclear(tokens,
				free_token), NULL);
	ft_lstadd_back(tokens, node);
	return (NOTNULL);
}

/*
 * @brief No need to check node->content if node is valid
 */
static void	*get_tokens_escaping_norms_2(t_list **line_lst,
		t_list *line_lst_head, t_list **tokens)
{
	t_list	*token_node;

	if (line_lst == NULL || *line_lst == NULL)
		return (NULL);
	if (tokens == NULL)
		return (NULL);
	token_node = get_token_node(*line_lst);
	if (token_node == NULL)
		return (ft_lstclear(&line_lst_head, free), ft_lstclear(tokens,
				free_token), NULL);
	if (((t_token *)token_node->content)->type == TOKEN_WHITE_SPACE
		&& is_last_token_type_space(*tokens) == true)
		return (ft_lstdelone(token_node, free_token), NOTNULL);
	ft_lstadd_back(tokens, token_node);
	return (NOTNULL);
}

static void rm_sp(t_list **tokens)
{
	remove_front_spaces(tokens);
	remove_back_spaces(tokens);
}

t_list	*get_tokens(char *line)
{
	t_list	*line_lst;
	t_list	*line_lst_head;
	t_list	*tokens;

	(void)!(tokens = NULL, line_lst = split_line(line),
		line_lst_head = line_lst);
	if (line_lst == NULL)
		return (NULL);
	while (line_lst != NULL)
	{
		if (ft_strcmp(line_lst->content, "\"") == 0
			|| ft_strcmp(line_lst->content, "\'") == 0)
		{
			if (get_tokens_escaping_norms_1(&line_lst, line_lst_head,
					&tokens) == NULL)
				return (NULL);
		}
		else if (get_tokens_escaping_norms_2(&line_lst, line_lst_head,
				&tokens) == NULL)
			return (NULL);
		if (line_lst != NULL)
			line_lst = line_lst->next;
	}
	return (rm_sp(&tokens), ft_lstclear(&line_lst_head, free), tokens);
}
