/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:44:31 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/14 18:54:27 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"
#include <stdio.h>


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

void	print_tokens(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL)
        {
		ft_fprintf(STDOUT_FILENO, "(null) ");
                return ;
        }
	while (tokens)
	{
		token = (t_token *)tokens->content;
		ft_fprintf(STDOUT_FILENO, "data: \"%s\" %s, ", token->data, get_token_type(token->type));
		fflush(stdout);
		tokens = tokens->next;
	}
}

static bool	is_ws_found(char *s)
{
	return (ft_strcmp(s, " ") == 0 || ft_strcmp(s, "\t") == 0);
}

static bool	if_escape(t_token *tok)
{
	return (is_word_and_space_found(tok)
		&& count_spaces(tok->data) != (int)ft_strlen(tok->data));
}

t_list	*get_word_tokens(t_token *token)
{
	t_list	*sptw;
	t_list	*wordt;
	t_list	*wordt_node;
	t_list	*sptw_head;

	if (token == NULL)
		return (NULL);
	sptw = ft_split_pro_max(token->data, " \t\n");
	(void)!(sptw_head = sptw, wordt = NULL);
	if (sptw == NULL)
		return (NULL);
	while (sptw && sptw->content)
	{
		if (is_ws_found(sptw->content))
			wordt_node = create_token_node(TOKEN_WHITE_SPACE, " ");
		else
			wordt_node = create_token_node(TOKEN_WORD, sptw->content);
		if (wordt_node == NULL)
			return (ft_lstclear(&sptw_head, free), ft_lstclear(&wordt,
					free_token), NULL);
		ft_lstadd_back(&wordt, wordt_node);
		sptw = sptw->next;
	}
	return (ft_lstclear(&sptw_head, free), wordt);
}

void	split_enhanced_tokens(t_list **tokens)
{
	t_list	*tokens_tmp;
	t_token	*tok;
	t_list	*wordt;

	tokens_tmp = *tokens;
	while (tokens_tmp)
	{
		tok = tokens_tmp->content;
		if (if_escape(tok))
		{
			wordt = get_word_tokens(tok);
			if (wordt == NULL)
				return ;
			ist(tokens, &tokens_tmp, wordt);
			continue ;
		}
		else if (tok->data == NULL)
		{
			del_token(&tokens_tmp, tokens);
			continue ;
		}
		tokens_tmp = tokens_tmp->next;
	}
}

t_list	*expand(t_list *tokens, t_list *env)
{
	t_list	*enhanced_tokens;
	t_list	*tmp;

	enhanced_tokens = get_enhanced_tokens(tokens, "$*");
	if (enhanced_tokens == NULL)
		return (NULL);
	expand_dollar(&enhanced_tokens, env);
	tmp = expand_wildcard(enhanced_tokens);
	if (tmp == NULL)
	{
		if (enhanced_tokens == NULL)
			return (NULL);
		split_enhanced_tokens(&enhanced_tokens);
		return (enhanced_tokens);
	}
	ft_lstclear(&enhanced_tokens, free_token);
	return (tmp);
}
