/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_api.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:05:16 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/24 11:46:08 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/expansion.h"

static char	*expand_word(t_list *tokenized_word, t_list *env)
{
	char	*str;
	t_list	*expanded_tokenized_word;

	if (tokenized_word == NULL || env == NULL)
		return (NULL);
	expanded_tokenized_word = expand_me(tokenized_word, env);
	if (expanded_tokenized_word == NULL)
		return (NULL);
	str = tokens_to_str(expanded_tokenized_word);
	ft_lstclear(&expanded_tokenized_word, free_token);
	return (str);
}

void	expand_command(char **command, t_list *tokenized_command, t_list *env)
{
	if (command == NULL || tokenized_command == NULL || env == NULL)
		return ;
	*command = expand_word(tokenized_command, env);
}

void	expand_filename(char **arguments, t_list *tokenized_filename,
		t_list *env)
{
	char	*filename;

	if (arguments == NULL || tokenized_filename == NULL || env == NULL)
		return ;
	filename = expand_word(tokenized_filename, env);
	if (ft_strchr(filename, ' ') != NULL)
	{
		ft_fprintf(STDOUT_FILENO, "bash: *: ambiguous redirect");
		filename = (free(filename), NULL);
		return ;
	}
}

t_list	*expand_arguments(t_list *tokenized_arguments, t_list *env)
{
	t_list	*arguments_lst;
	t_list	*word;
	char	*expanded_argument;
	t_list	*expanded_argument_node;

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
		expanded_argument_node = ft_lstnew(expanded_argument);
		if (expanded_argument_node == NULL)
			return (ft_lstclear(&arguments_lst, free), NULL);
		ft_lstadd_back(&arguments_lst, expanded_argument_node);
		if (tokenized_arguments == NULL)
			break ;
		tokenized_arguments = tokenized_arguments->next;
	}
	return (arguments_lst);
}
