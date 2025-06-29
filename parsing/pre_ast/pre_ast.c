/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:00:05 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/29 16:13:36 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/pre_ast.h"
#include <stdio.h>
#include <stdlib.h>

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

void *insert_filename_token(char *filename, t_list *start, t_list *end, t_list **tokens)
{
        t_list *tokenized_file_name_start;
        t_list *node_to_del;
        t_list *filename_token_node;

        if (filename == NULL || start == NULL || end == NULL || tokens == NULL)
                return (NULL);
        
        tokenized_file_name_start = start;
        skip_front_spaces(&tokenized_file_name_start);

        while (tokenized_file_name_start && tokenized_file_name_start != end)
        {
                node_to_del = tokenized_file_name_start;
                tokenized_file_name_start = tokenized_file_name_start->next;
                ft_lst_rm_one(tokens, node_to_del, free_token);
        }
        filename_token_node = create_token_node(TOKEN_WORD, filename);
        if (filename_token_node == NULL)
                return (NULL);
        ft_add_node(start, filename_token_node);
        return (NOTNULL);
}

static void	handle_heredocs(t_list **tokens)
{
	t_list	*current_token;
	char	*filename;
	t_list	*tokenized_file_name;
        t_list *start;

        (void) start;
	if (tokens == NULL || *tokens == NULL)
		return ;
	current_token = *tokens;
	while (current_token)
	{
		if (check_token_type(current_token->content, TOKEN_HEREDOC) == true)
		{
			current_token = current_token->next;
                        start = current_token;
			tokenized_file_name = get_filename(&current_token);
			filename = handle_heredoc(tokenized_file_name, NULL);
			if (filename == NULL)
				return (ft_lstclear(&tokenized_file_name, free_token));
                        insert_filename_token(filename, start, current_token, tokens);
                        continue ;
		}
		current_token = current_token->next;
	}
}

void	pre_ast(t_list **tokens)
{
	if (tokens == NULL)
		return ;
	enhance_redirections(tokens);
	handle_heredocs(tokens);
        print_tokens_data(*tokens);
        exit(0);
}
