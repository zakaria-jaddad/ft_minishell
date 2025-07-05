/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_api.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:29:20 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/04 00:51:41 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing/expansion.h"

static char	**create_cmd_and_args(t_list *command, t_list *arguments)
{
	char	**cmds;
	char	**args;

	cmds = list_to_double_pointer(command);
	args = list_to_double_pointer(arguments);
	ft_lstclear(&command, free);
	ft_lstclear(&arguments, free);
	return (arr_add_front(cmds, args));
}

t_list	*expand_command(t_list *tokenized_command, t_list *env)
{
	t_list	*expanded_word;

	if (tokenized_command == NULL || env == NULL)
		return (NULL);
	expanded_word = expand_word(tokenized_command, env);
	return (expanded_word);
}

void	expand_filename(char **filename, t_list *filenamet, t_list *env)
{
	t_list	*filename_lst;

	if (filename == NULL || filenamet == NULL || env == NULL)
		return ;
	filename_lst = expand_word(filenamet, env);
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

t_list	*expand_arguments(t_list *argt, t_list *env)
{
	t_list	*arguments_lst;
	t_list	*wordt;
	t_list	*expanded_argument;

	arguments_lst = NULL;
	while (argt)
	{
		wordt = get_tokenizd_word(&argt);
		if (wordt == NULL)
			return (ft_lstclear(&arguments_lst, free), NULL);
		expanded_argument = expand_word(wordt, env);
		ft_lstclear(&wordt, free_token);
		if (expanded_argument == NULL)
			continue ;
		ft_lstadd_back(&arguments_lst, expanded_argument);
		if (argt == NULL)
			break ;
		argt = argt->next;
	}
	return (arguments_lst);
}

char	**expand_all(t_list *cmdt, t_list *argt, t_list *env)
{
	t_list	*command;
	t_list	*arguments;
	t_list	*argtdup;

	command = expand_command(cmdt, env);
	argtdup = dup_tokens(argt, ft_lstlast(argt), true);
	pre_expansion(command, cmdt, &argtdup);
	arguments = expand_arguments(argtdup, env);
	ft_lstclear(&argtdup, free_token);
	return (create_cmd_and_args(command, arguments));
}
