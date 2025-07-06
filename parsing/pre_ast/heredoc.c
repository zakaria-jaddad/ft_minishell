/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:27:40 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/06 15:35:52 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uintptr_t	open_and_read_urandom(void)
{
	uintptr_t	c;
	int			fd;
	int			bytes_read;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
	{
		return (1);
	}
	bytes_read = read(fd, &c, sizeof(uintptr_t));
	if (bytes_read != (sizeof(uintptr_t)))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (c);
}

char	*get_address(void *var)
{
	char			str[19];
	char			*charset;
	unsigned long	ptr;
	int				i;
	int				idx;

	charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXUZabcdefghijklmnopqrstuvwxyz";
	ptr = (unsigned long)var;
	str[0] = '.';
	i = 1;
	while (i < 18)
	{
		idx = ((ptr % 16) + (open_and_read_urandom() % 16)) % 16;
		str[i] = charset[idx];
		ptr /= 16;
		i++;
	}
	str[18] = '\0';
	return (ft_strjoin("/tmp/", str));
}

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

char	*expand_arr(char **arr, t_list *envs)
{
	int		i;
	char	*tmp;
	char	*res;
	t_env	*env;

	i = 0;
	res = NULL;
	while (arr[i])
	{
		if (arr[i][0] == '$' && arr[i][1])
		{
			env = get_env(envs, arr[i] + 1);
			if (env)
				tmp = ft_strdup(env->value);
			else
				tmp = ft_strdup("");
			free(arr[i]);
			arr[i] = tmp;
		}
		tmp = ft_strjoin(res, arr[i]);
		free(res);
		res = tmp;
		i++;
	}
	return (res);
}

char	*expand_heredoc(char *str, t_list *env_list)
{
	char	**arr;
	int		i;
	int		j;
	int		k;
	char	*res;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == '\n' || str[i] == '$' || str[i] == '"' || str[i] == '\'')
			j++;
	arr = malloc(sizeof(char *) * (j + 2));
	i = -1;
	j = 0;
	k = 0;
	while (str[++i])
	{
		if (str[i] == '\n' || str[i] == '$' || str[i] == '"' || str[i] == '\'')
		{
			arr[j++] = ft_substr(str, k, i - k);
			k = i;
		}
	}
	arr[j++] = ft_substr(str, k, i - k);
	arr[j] = NULL;
	res = expand_arr(arr, env_list);
	return (res);
}

char	*run_heredoc(char *dilimiter, int expand, t_list *env_list)
{
	char	*line;
	char	*res;
	int		fd;
	pid_t	pid;

	line = get_address(dilimiter);
	if (access(line, F_OK) == 0)
		line = get_address(line);
	pid = fork();
	if (pid == 0)
	{
		if (signal(SIGINT, handle_ctr_c_fork) == SIG_ERR)
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
		if (expand && res)
			res = expand_heredoc(res, env_list);
		if (res)
		{
			write(fd, res, ft_strlen(res));
		}
		close(fd);
		free(res);
		exit(0);
	}
	else
		wait(&fd);
	if (fd > 0)
		return (NULL);
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
			|| token->type == TOKEN_DOUBLE_QUOTE_WORD)
			expand = 0;
		tokens = tokens->next;
	}
	return (run_heredoc(str, expand, env_list));
}
