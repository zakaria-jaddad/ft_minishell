/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_api.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:05:16 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/01 12:52:25 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"
#include "../../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	count_spaces(char *s)
{
	int	spaces;

	spaces = 0;
	while (*s)
	{
		if (*s == ' ')
			spaces++;
		s++;
	}
	return (spaces);
}
static bool	check_spaces(char *str)
{
	return (count_spaces(str) == (int)ft_strlen(str));
}

static int	is_valid_word_token(int type)
{
	return (type == TOKEN_WORD || type == TOKEN_DOUBLE_QUOTE_WORD
		|| type == TOKEN_SINGLE_QUOTE_WORD);
}

t_list	*extract_words_list(t_list *tokens)
{
	t_list	*result;
	t_token	*tok;
	char	*dup;
	t_list	*new_node;
	t_list	*tokenized_word;

	result = NULL;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok && is_valid_word_token(tok->type) && tok->data
			&& check_spaces(tok->data) == false)
		{
			tokenized_word = get_filename(&tokens);
			if (tokenized_word == NULL)
				return (ft_lstclear(&result, free), NULL);
			dup = tokens_to_str(tokenized_word);
			if (dup == NULL)
				return (ft_lstclear(&tokenized_word, free_token),
					ft_lstclear(&result, free), NULL);
			new_node = ft_lstnew(dup);
			if (new_node == NULL)
				return (free(dup), ft_lstclear(&tokenized_word, free_token),
					ft_lstclear(&result, free), NULL);
			ft_lstadd_back(&result, new_node);
			continue ;
		}
		tokens = tokens->next;
	}
	return (result);
}

static t_list	*expand_word(t_list *tokenized_word, t_list *env)
{
	t_list	*expanded_tokenized_word;
	t_list	*expansion_lst;

	if (tokenized_word == NULL || env == NULL)
		return (NULL);
	expanded_tokenized_word = expand(tokenized_word, env);
	if (expanded_tokenized_word == NULL)
		return (NULL);
	expansion_lst = extract_words_list(expanded_tokenized_word);
	return (expansion_lst);
}

t_list	*expand_command(t_list *tokenized_command, t_list *env)
{
	t_list	*expanded_word;

	expanded_word = expand_word(tokenized_command, env);
	if (tokenized_command == NULL || env == NULL)
		return (NULL);
	return (expanded_word);
}

void	expand_filename(char **filename, t_list *tokenized_filename,
		t_list *env)
{
	t_list *filename_lst;
	if (filename == NULL || tokenized_filename == NULL || env == NULL)
		return ;
	filename_lst = expand_word(tokenized_filename, env);
	if (filename_lst == NULL)
		return ;
	if (ft_lstsize(filename_lst) > 1)
	{
		ft_fprintf(STDERR_FILENO, "bash: *: ambiguous redirect\n");
		status_x(1, true);
		ft_lstclear(&filename_lst, free);
		return ;
	}
	*filename = ft_strdup(filename_lst->content);
	ft_lstclear(&filename_lst, free);
}

t_list	*expand_arguments(t_list *tokenized_arguments, t_list *env)
{
	t_list	*arguments_lst;
	t_list	*word;
	t_list	*expanded_argument;

	arguments_lst = NULL;
	while (tokenized_arguments)
	{
		word = get_tokenizd_word(&tokenized_arguments);
		if (word == NULL)
			return (ft_lstclear(&arguments_lst, free), NULL);
		expanded_argument = expand_word(word, env);
		ft_lstclear(&word, free_token);
		if (expanded_argument == NULL)
			return (ft_lstclear(&arguments_lst, free), NULL);
		ft_lstadd_back(&arguments_lst, expanded_argument);
		if (tokenized_arguments == NULL)
			break ;
		tokenized_arguments = tokenized_arguments->next;
	}
	return (arguments_lst);
}

t_list	*expand_arguments_v2(t_list *cmd_lst, t_list *tokenized_arguments, t_list *env)
{
	if (cmd_lst == NULL)
		return (expand_arguments(tokenized_arguments, env));
	
	for (t_list *tmp = cmd_lst; tmp != NULL; tmp = tmp->next)
	{
		printf("\"%s\" ", (char *)tmp->content);
		fflush(stdout);
	}
	printf("\n");
	return (NULL);
}
