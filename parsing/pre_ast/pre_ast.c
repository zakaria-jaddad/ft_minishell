/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:00:05 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/25 21:29:18 by zajaddad         ###   ########.fr       */
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

static void	handle_heredocs(t_list **tokens)
{
	t_list	*current_token;
	char	*filename;
	t_list	*tokenized_file_name;

	if (tokens == NULL || *tokens == NULL)
		return ;
	current_token = *tokens;
	while (current_token)
	{
		if (check_token_type(current_token->content, TOKEN_HEREDOC) == true)
		{
			current_token = current_token->next;
			tokenized_file_name = get_filename(&current_token);
			filename = handle_heredoc(tokenized_file_name, NULL);
			if (filename == NULL)
				return (ft_lstclear(&tokenized_file_name, free_token));
			printf("filename: %s\n", filename);
		}
		if (current_token == NULL)
			break ;
		current_token = current_token->next;
	}
}

void	pre_ast(t_list **tokens)
{
	if (tokens == NULL)
		return ;
	enhance_redirections(tokens);
	handle_heredocs(tokens);
}
