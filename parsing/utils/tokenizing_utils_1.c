/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:32:08 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/07 19:43:05 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include <stdlib.h>

/*
 * @brief frees t_token object
 * @return: Void
 */
void	free_token(t_token *token)
{
	token->data = (free(token->data), NULL);
}

/*
 * @brief frees tokens list memory (nodes and content)
 * @return: Void
 */
void	free_tokens(t_list **tokens)
{
	t_list	*tokens_node;

	tokens_node = *tokens;
	while (tokens_node != NULL)
	{
		free_token(tokens_node->content);
		tokens_node = tokens_node->next;
	}
	ft_lstclear(tokens, free);
	*tokens = NULL;
}

/*
 * @brief Creates a t_token object, returns it's
 *      address
 * @return: when success returns t_token object
 *      address.
 *      when error returns NULL
 *
 *  if token_type is TOKEN_SINGLE_QUOTE_WORD don't add \ to $
 */
t_token	*create_token(t_token_type token_type, char *token_data)
{
	t_token	*token;
        char **foo;
        
	if (token_data == NULL)
		token_data = NULL;
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = token_type;
        token->data = NULL;
        if (token_type == TOKEN_SINGLE_QUOTE_WORD)
	        token->data = ft_strdup(token_data);
        else
        {
                foo = ft_split(token_data, '$');
                if (foo == NULL)
                        return (free_token(token), token = NULL);
                while (*foo)
                {
                        /* FIX: 
                         * "ls -lah$a$a$a"$a ---> "ls -lah\$a\$a\$aa"
                         * THIS ISN'T THE RIGHT APPROACH!!!
                         */
                        append_str(&token->data, *foo++); // foo[i++]
                        if (*foo == NULL)
                                break ;
                        append_str(&token->data, ft_strdup("\\$"));
                }
        }
	if (token_data == NULL)
		return (free_token(token), NULL);
	return (token);
}

/*
 * @brief Function definition for creating list node,
 *      which has the content of a token.
 * @param:
 *      token_type: token type
 *      token_data: current token data
 * @return: when success returns list node,
 *      when error returns NULL and free memory
 *      of the created token
 */
t_list	*create_token_node(t_token_type token_type, char *token_data)
{
	t_list	*node;
	t_token	*token;

	token = create_token(token_type, token_data);
	if (token == NULL)
		return (NULL);
	node = ft_lstnew(token);
	if (node == NULL)
		return (free_token(token), token = NULL, NULL);
	return (node);
}

/*
 * @brief Tokenize double and single quotes
 * @param:
 *      quote_type: string contains either """ or "'"
 *      token_type:
 *      line_lst: address of split lines
 * @return:
 *      if success returns a list node with the tokenized content
 *      if error returns NULL and frees the allocated token
 */
t_list	*tokenize_quotes(char *quote_type, t_token_type token_type,
		t_list **line_lst)
{
	t_token	*token;
	t_list	*node;
        char *token_data;

        token_data = NULL;
	*line_lst = (*line_lst)->next;
	if (line_lst == NULL || *line_lst == NULL)
		return (NULL);
	while (*line_lst != NULL && ft_strcmp((char *)(*line_lst)->content,
		quote_type) != 0)
	{
		append_str(&token_data, (*line_lst)->content);
		*line_lst = (*line_lst)->next;
	}
	token = create_token(token_type, token_data);
	if (token == NULL)
		return (NULL);
	node = ft_lstnew(token);
	if (node == NULL)
		return (free_token(token), token = NULL, NULL);
	return (node);
}
