/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:27:40 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/13 01:28:46 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/minishell.h"
#include "../../includes/parsing/pre_ast.h"
#include <readline/readline.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*open_heredoc(char *dilimiter)
{
	char	*res;
	char	*tmp;
	char	*line;

	line = readline("> ");
	res = NULL;
	while (line != NULL && ft_strcmp(line, dilimiter) != 0)
	{
		tmp = ft_strjoin(res, line);
		free(res);
		res = tmp;
		tmp = ft_strjoin(res, "\n");
		free(res);
		res = tmp;
		free(line);
		line = readline("> ");
	}
	free(line);
	return (res);
}

char	*expand_heredoc(char *str, t_list *env_list)
{
	char	**arr;
	int		i;
	int		j;
	int		k;
	char	*res;

	if (str == NULL)
		return (NULL);
	j = count_allocate(str);
	arr = malloc(sizeof(char *) * (j + 2));
	if (arr == NULL)
		return (NULL);
	(void)!(i = -1, j = 0, k = 0);
	while (str[++i])
		if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A'
				&& str[i] <= 'Z') && str[i] != '_')
			(void)!(arr[j++] = ft_substr(str, k, i - k), k = i);
	arr[j++] = ft_substr(str, k, i - k);
	arr[j] = NULL;
	res = expand_arr(arr, env_list);
	return (free(str), res);
}

void	heredoc_fork(char *dilimiter, char *line, int expand, t_list *env_list)
{
	int		fd;
	char	*res;

	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		ft_fprintf(STDERR_FILENO, "signal: error handling ctr+c!!\n");
		exit(1);
	}
	res = open_heredoc(dilimiter);
	fd = open(line, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(line);
		exit(1);
	}
	if (expand)
		res = expand_heredoc(res, env_list);
	if (res)
		write(fd, res, ft_strlen(res));
	close(fd);
	free(res);
	exit(0);
}

char	*run_heredoc(char *dilimiter, int expand, t_list *env_list)
{
	char	*line;
	int		fd;
	pid_t	pid;

	line = get_address(dilimiter);
	fd = 0;
	if (line == NULL)
		return (free(dilimiter), NULL);
	if (access(line, F_OK) == 0)
	{
		line = (free(line), NULL);
		line = get_address(dilimiter);
	}
	pid = fork();
	if (pid == 0)
		heredoc_fork(dilimiter, line, expand, env_list);
	else
		wait(&fd);
	free(dilimiter);
	if (fd > 0)
		return (free(line), status_x(1, 1), NULL);
	return (line);
}

char	*handle_heredoc(t_list *tokens, t_list *env_list)
{
	t_token	*token;
	int		expand;
	char	*str;

	if (!tokens)
		return (NULL);
	expand = 1;
	str = tokens_to_str(tokens);
	while (tokens)
	{
		token = tokens->content;
		if (token->type == TOKEN_DOUBLE_QUOTE_WORD
			|| token->type == TOKEN_SINGLE_QUOTE_WORD)
			expand = 0;
		tokens = tokens->next;
	}
	return (run_heredoc(str, expand, env_list));
}
