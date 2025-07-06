/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:00:05 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/06 00:15:09 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/pre_ast.h"

static void	enhance_redirections(t_list **tokens)
{
	t_list	*current_token;

	if (tokens == NULL || *tokens == NULL)
		return ;
	current_token = *tokens;
	while (current_token)
	{
		if (is_redirection(current_token->content) == true)
		{
			enhance_redirection(&current_token, tokens);
			continue ;
		}
		current_token = current_token->next;
	}
}

void	*insert_filename_token(char *filename, t_list *start, t_list *end,
		t_list **tokens)
{
	t_list	*tokenized_file_name_start;
	t_list	*node_to_del;
	t_list	*filenametn;

	if (start == NULL || tokens == NULL)
		return (NULL);
	tokenized_file_name_start = start->next;
	skip_front_spaces(&tokenized_file_name_start);
	while (tokenized_file_name_start && tokenized_file_name_start != end)
	{
		node_to_del = tokenized_file_name_start;
		tokenized_file_name_start = tokenized_file_name_start->next;
		ft_lst_rm_one(tokens, node_to_del, free_token);
	}
        if (filename == NULL)
	        filenametn = create_token_node(TOKEN_WORD, "NULL");
        else
	        filenametn = create_token_node(TOKEN_WORD, filename);
	if (filenametn == NULL)
		return (NULL);
	if (start->next == NULL)
		start->next = filenametn;
	else
		ft_add_node(start, filenametn);
	return (NOTNULL);
}

static void	handle_heredocs(t_list **tokens, t_list *envs)
{
	t_list	*tok;
	char	*filename;
	t_list	*filenamet;
	t_list	*start;

	(void)start;
	if (tokens == NULL || *tokens == NULL)
		return ;
	tok = *tokens;
	while (tok)
	{
		if (check_token_type(tok->content, TOKEN_HEREDOC) == true)
		{
			(void)!(start = tok, tok = tok->next,
				filenamet = get_filename(&tok));
			filename = handle_heredoc(filenamet, NULL);
			ft_lstclear(&filenamet, free_token);
			if (NULL == insert_filename_token(filename, start, tok, tokens))
				return (free(filename));
			free(filename);
			continue ;
		}
		tok = tok->next;
	}
}

void	pre_ast(t_list **tokens, t_list *envs)
{
	if (tokens == NULL)
		return ;
	enhance_redirections(tokens);
	handle_heredocs(tokens, envs);
}
