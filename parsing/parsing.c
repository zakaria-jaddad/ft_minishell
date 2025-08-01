/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/17 05:15:54 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing/parsing.h"

#define MHCE "bash: maximum here-document count exceeded\n"

bool	heredoc_limit(t_list *tokens)
{
	t_token	*tok;
	int		i;

	i = 0;
	while (tokens && i < 17)
	{
		tok = tokens->content;
		if (tok->type == TOKEN_HEREDOC)
			i++;
		tokens = tokens->next;
	}
	if (i == 17)
	{
		ft_fprintf(STDERR_FILENO, MHCE);
		return (true);
	}
	return (false);
}

void	clear_cmd(t_cmd *cmd)
{
	free_ast(cmd);
}

t_cmd	*parse_cmd(char *line, t_list *env_lst)
{
	t_list	*tokens;
	t_cmd	*cmd;

	(void)env_lst;
	cmd = NULL;
	tokens = get_tokens(line);
	if (tokens == NULL)
		return (NULL);
	if (syntax_check(tokens) == false)
		return (ft_lstclear(&tokens, free_token), status_x(258, true), NULL);
	if (heredoc_limit(tokens) == true)
		return (ft_lstclear(&tokens, free_token), exit(2), NULL);
	if (pre_ast(&tokens, env_lst) == false)
		return (ft_lstclear(&tokens, free_token), NULL);
	if (syntax_check(tokens) == false)
		return (ft_lstclear(&tokens, free_token), status_x(258, true), NULL);
	cmd = ast(&tokens);
	if (cmd == NULL)
		return (ft_lstclear(&tokens, free_token), NULL);
	ft_lstclear(&tokens, free_token);
	return (cmd);
}
