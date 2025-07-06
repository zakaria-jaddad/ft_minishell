/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:27:40 by mouait-e          #+#    #+#             */
/*   Updated: 2025/07/01 16:27:40 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include <readline/readline.h>
#include <stdint.h>
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

char	*run_heredoc(char *dilimiter, int expand, t_list *env_list)
{
	char	*line;
	char	*res;
	int		fd;

	(void)env_list;
	(void)expand;
	res = open_heredoc(dilimiter);
	line = get_address(dilimiter);
	if (access(line, F_OK) == 0)
		line = get_address(line);
	fd = open(line, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (free(line), NULL);
	if (res)
		write(fd, res, ft_strlen(res));
	close(fd);
	free(res);
	return (line);
}

char	*handle_heredoc(t_list *tokens, t_list *env_list)
{
	t_token	*token;
	int		expand;
	char	*str;
	char *res;

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
	res = run_heredoc(str, expand, env_list);
	free(str);
	return (res);
}
