/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:32:08 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 02:18:26 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/tokenize.h"
#include <stdlib.h>

/*
 * @brief frees t_token object
 * @return: Void
 */
void	free_token(void *token)
{
	if (token == NULL)
		return ;
	((t_token *)token)->data = (free(((t_token *)token)->data), NULL);
	free(token);
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

	if (token_data == NULL)
		token_data = "";
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = token_type;
	token->data = ft_strdup(token_data);
	if (token->data == NULL)
		return (free(token), NULL);
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
t_list	*tokenize_quotes(char *quote_type, t_token_type token_type, t_list **ls)
{
	t_token	*token;
	t_list	*node;
	char	*tod;

	if (ls == NULL || *ls == NULL)
		return (NULL);
	(void)!(tod = NULL, *ls = (*ls)->next);
	while (*ls != NULL && ft_strcmp((char *)(*ls)->content, quote_type) != 0)
	{
		append_str(&tod, (*ls)->content);
		if (tod == NULL)
			return (free(tod), tod = NULL, NULL);
		*ls = (*ls)->next;
	}
	if (*ls != NULL && ft_strcmp((*ls)->content, quote_type) == 0)
	{
		(void)!(token = create_token(token_type, tod), free(tod), 0);
		if (token == NULL)
			return (NULL);
		node = ft_lstnew(token);
		if (node == NULL)
			return (free_token(token), token = NULL, NULL);
		return (node);
	}
	return (invalid_quote(quote_type, tod), NULL);
}
