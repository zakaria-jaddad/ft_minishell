/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:32:08 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/09 19:39:19 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/parsing.h"

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
t_list	*tokenize_quotes(char *quote_type, t_token_type token_type,
		t_list **line_lst)
{
	t_token	*token;
	t_list	*node;
	char	*token_data;

	token_data = NULL;
	if (line_lst == NULL || *line_lst == NULL)
		return (NULL);
	*line_lst = (*line_lst)->next;
	while (*line_lst != NULL && ft_strcmp((char *)(*line_lst)->content,
		quote_type) != 0)
	{
		append_str(&token_data, (*line_lst)->content);
		if (token_data == NULL)
			return (free(token_data), token_data = NULL, NULL);
		*line_lst = (*line_lst)->next;
	}
	token = create_token(token_type, token_data);
	token_data = (free(token_data), NULL);
	if (token == NULL)
		return (NULL);
	node = ft_lstnew(token);
	if (node == NULL)
		return (free_token(token), token = NULL, NULL);
	return (node);
}

void	print_tokens(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL)
		printf("(null)");
	while (tokens)
	{
		token = (t_token *)tokens->content;
		printf("data: \"%s\" %s, ", token->data, get_token_type(token->type));
		fflush(stdout);
		tokens = tokens->next;
	}
}

