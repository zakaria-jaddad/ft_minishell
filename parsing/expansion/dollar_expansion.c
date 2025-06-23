/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:32:40 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:32 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

static bool	is_valid_dollar_with_qs_next(t_list *current_token_node)
{
	t_token	*current_token;

	if (current_token_node == NULL)
		return (false);
	current_token = current_token_node->content;
	if (current_token == NULL)
		return (false);
	return (ft_strcmp(current_token->data, "$") == 0
		&& check_token_type(current_token, TOKEN_WORD)
		&& (peak_next(current_token_node) == TOKEN_DOUBLE_QUOTE_WORD
			|| peak_next(current_token_node) == TOKEN_SINGLE_QUOTE_WORD));
}

static bool	is_valid_dollar_with_valid_var(t_list *current_token_node)
{
	t_token	*current_token;

	if (current_token_node == NULL)
		return (false);
	current_token = current_token_node->content;
	if (current_token == NULL)
		return (false);
	return (ft_strcmp(current_token->data, "$") == 0
		&& (check_token_type(current_token, TOKEN_WORD)
			|| check_token_type(current_token, TOKEN_DOUBLE_QUOTE_WORD))
		&& peak_next(current_token_node) == current_token->type);
}

static void del_node_and_go_next(t_list **tokens, t_list **token_head)
{
	t_list	*node_to_del;

        if (tokens == NULL || *tokens == NULL)
                return ;
        if (token_head == NULL || *token_head == NULL)
                return ;

        node_to_del = *tokens;
        *tokens = (*tokens)->next;
        ft_lst_rm_one(node_to_del, free);
}

static void update_current_token(t_list *current_token_node, t_list *env)
{
        char	*key;
        t_env	*var;
        t_token	*current_token;

        if (current_token_node == NULL)       
                return ;
        current_token = current_token_node->content;
        if (current_token == NULL)
                return ;

        key = current_token->data;
        var = get_env(env, key);
        free(current_token->data);
        if (var == NULL)
                current_token->data = ft_strdup(key);
        else
                current_token->data = ft_strdup(var->value);
}

t_list	*expand_dollar(t_list *tokens, t_list *env)
{
	t_list	*tokens_head;
	t_token	*current_token;

	while (tokens)
	{
		current_token = tokens->content;
		if (ft_strchr(current_token->data, '$') != NULL)
		{
			if (is_valid_dollar_with_qs_next(tokens) == true)
                                del_node_and_go_next(&tokens, &tokens_head);
			else if (is_valid_dollar_with_valid_var(tokens) == true)
			{
                                del_node_and_go_next(&tokens, &tokens_head);
                                update_current_token(tokens, env);
			}
		}
                (void)!(tokens = tokens->next);
	}
	return (tokens_head);
}
