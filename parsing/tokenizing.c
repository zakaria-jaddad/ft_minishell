/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:37:13 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/07 19:23:21 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <stdbool.h>

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
                /* TODO:  don't add \ to $ if found qeep it the same */
		node = tokenize_quotes("\'", TOKEN_SINGLE_QUOTE_WORD, line_lst);
	if (node == NULL)
		return (ft_lstclear(&line_lst_head, free), free_tokens(tokens), NULL);
	if (check_equal_in_last_token(*tokens) == true
		|| is_last_token_type_word(*tokens) == true)
	{
		// TODO: content might bee null HANDLE SEGV
		append_last_toke_data(tokens, ((t_token *)node->content)->data);
		(free_token(node->content), ft_lstdelone(node, free));
	}
	else
		ft_lstadd_back(tokens, node);
	return (NOTNULL);
}

static void	*get_tokens_escaping_norms_2(t_list **line_lst,
		t_list *line_lst_head, t_list **tokens)
{
	t_list	*node;

	if (line_lst == NULL || *line_lst == NULL)
		return (NULL);
	if (tokens == NULL)
		return (NULL);
	node = get_token_node(*line_lst);
	if (node == NULL)
		return (ft_lstclear(&line_lst_head, free), free_tokens(tokens), NULL);
	if (is_last_token_type_word(*tokens) == true
		&& is_token_type_word(node) == true)
	{
		append_last_toke_data(tokens, ((t_token *)node->content)->data);
		(free_token(node->content), ft_lstdelone(node, free));
	}
	else
		ft_lstadd_back(tokens, node);
	return (NOTNULL);
}

void	print_split(t_list *split)
{

	for (t_list *tmp = split; tmp != NULL; tmp = tmp->next)
	{
		fprintf(stderr, "\"%s\" ------> ", (char *) tmp->content);
		fflush(stdout);
	}
	printf("\n");
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
        print_split(line_lst);
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
	return (ft_lstclear(&line_lst_head, free), tokens);
}
