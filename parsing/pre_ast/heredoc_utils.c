/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:12:33 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:24:06 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing/pre_ast.h"

int	count_allocate(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
		if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A'
				&& str[i] <= 'Z') && str[i] != '_')
			j++;
	return (j);
}

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

char	*expand_arr(char **arr, t_list *envs)
{
	int		i;
	char	*tmp;
	char	*res;
	t_env	*env;
	char	*key;

	(void)!(i = 0, res = NULL);
	while (arr[i])
	{
		if (arr[i][0] == '$' && arr[i][1] != 0)
		{
			key = ft_substr(&arr[i][1], 0, ft_strlen(&arr[i][1]));
			env = get_env(envs, key);
			free(key);
			if (env)
				tmp = ft_strdup(env->value);
			else
				tmp = ft_strdup("");
			if (tmp != NULL)
				(void)!(free(arr[i]), arr[i] = tmp);
		}
		tmp = ft_strjoin(res, arr[i]);
		(void)!(free(res), res = tmp, i++);
	}
	return (ft_split_free(arr), res);
}
