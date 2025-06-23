/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:32:40 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/23 18:00:04 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"
#include <stdio.h>
#include <stdlib.h>
#define special_expansion " .,+-!@#$%^&*()[]{};:'\"<>/?|~`= \t\n"

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
	t_list	*next_token_node;
	t_token	*next_token;

	if (current_token_node == NULL)
		return (false);
	next_token_node = current_token_node->next;
	if (next_token_node == NULL)
		return (false);
	current_token = current_token_node->content;
	next_token = next_token_node->content;
	if (current_token == NULL || next_token == NULL)
		return (false);
	if (ft_strchr(special_expansion, *next_token->data) != NULL)
		return false;
	return (ft_strcmp(current_token->data, "$") == 0
		&& ft_strcmp(next_token->data, "$") != 0
		&& (check_token_type(current_token, TOKEN_WORD)
			|| check_token_type(current_token, TOKEN_DOUBLE_QUOTE_WORD))
		&& peak_next(current_token_node) == current_token->type);
}

static void	del_node_and_go_next(t_list **tokens, t_list **token_head)
{
	t_list	*node_to_del;

	if (tokens == NULL || *tokens == NULL)
		return ;
	if (token_head == NULL || *token_head == NULL)
		return ;
	node_to_del = *tokens;
	*tokens = (*tokens)->next;
	ft_lst_rm_one(token_head, node_to_del, free_token);
}

void	digit_expansion(char **str)
{
	char	*new_value;
	char	*tmp;

	if (str == NULL || *str == NULL)
		return ;
	new_value = ft_strdup(*str + 1);
	if (new_value == NULL)
		return ;
	tmp = *str;
	*str = new_value;
	free(tmp);
	return ;
}

char	*get_key(char *str, char *special)
{
	int	special_pos;

	special_pos = 0;
	while (str[special_pos] != 0 && &str[special_pos] != special)
		special_pos++;
	return (ft_substr(str, 0, special_pos));
}
static void	special_word_expansion(char **str, char *special, t_list *env)
{
	char	*key;
	char	*tmp;
	t_env	*var;

	if (str == NULL || *str == NULL || env == NULL || special == NULL)
		return ;
	key = get_key(*str, special);
	if (key == NULL)
		return ;
	var = get_env(env, key);
	tmp = *str;
	if (var == NULL)
		*str = ft_strjoin("", special);
	else
		*str = ft_strjoin(var->value, special);
	free(tmp);
	free(key);
	return ;
}

static void	simple_word_expansion(char **str, t_list *env)
{
	char	*tmp;
	t_env	*var;

	if (str == NULL || *str == NULL || env == NULL)
		return ;
	var = get_env(env, *str);
	tmp = *str;
	if (var == NULL)
		*str = ft_strdup("");
	else
		*str = ft_strdup(var->value);
	free(tmp);
}

static void	word_expansion(char **str, t_list *env)
{
	char	*special;

	if (str == NULL || *str == NULL)
		return ;
	special = ft_strpbrk(*str, special_expansion);
	if (special != NULL)
		return (special_word_expansion(str, special, env));
	simple_word_expansion(str, env);
}

static void	update_current_token(t_list *current_token_node, t_list *env)
{
	t_token	*current_token;

	if (current_token_node == NULL)
		return ;
	current_token = current_token_node->content;
	if (current_token == NULL)
		return ;
	if (ft_isdigit(*current_token->data) == true)
		return (digit_expansion(&current_token->data));
	word_expansion(&current_token->data, env);
}

static bool	is_valid_dollar_with_dollar(t_list *current_token_node)
{
	t_token	*current_token;
	t_list	*next_token_node;
	t_token	*next_token;

	if (current_token_node == NULL)
		return (false);
	next_token_node = current_token_node->next;
	if (next_token_node == NULL)
		return (false);
	current_token = current_token_node->content;
	next_token = next_token_node->content;
	if (current_token == NULL || next_token == NULL)
		return (false);
	return (ft_strcmp(current_token->data, "$") == 0
		&& ft_strcmp(next_token->data, "$") == 0);
}

static void	expand_dollar_escaping_norms(t_list **tokens, t_list **tokens_head,
		t_list *env)
{
	if (is_valid_dollar_with_qs_next(*tokens) == true)
		del_node_and_go_next(tokens, tokens_head);
	else if (is_valid_dollar_with_valid_var(*tokens) == true)
		(void)(del_node_and_go_next(tokens, tokens_head),
			update_current_token(*tokens, env));
}

t_list	*expand_dollar(t_list *tokens, t_list *env)
{
	t_list	*tokens_head;
	t_token	*current_token;

	tokens_head = tokens;
	while (tokens)
	{
		current_token = tokens->content;
		if (ft_strchr(current_token->data, '$') != NULL)
		{
			if (is_valid_dollar_with_qs_next(tokens) == true
				|| is_valid_dollar_with_valid_var(tokens) == true)
			{
				expand_dollar_escaping_norms(&tokens, &tokens_head, env);
				continue ;
			}
			else if (is_valid_dollar_with_dollar(tokens) == true)
				tokens = tokens->next;
		}
		if (tokens == NULL)
			break ;
		tokens = tokens->next;
	}
	return (tokens_head);
}
