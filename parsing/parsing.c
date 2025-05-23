/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 16:21:01 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <dirent.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* DT_BLK      This is a block device. */
/* DT_CHR      This is a character device. */
/* DT_DIR      This is a directory. */
/* DT_FIFO     This is a named pipe (FIFO). */
/* DT_LNK      This is a symbolic link. */
/* DT_REG      This is a regular file. */
/* DT_SOCK     This is a UNIX domain socket. */
/* DT_UNKNOWN  The file type could not be determined. */




























/*
 * @brief
 * @info
 *      fi: file information
 * @param
 * @param
 * @return List of matched files to the given pattern
 */














void	ft_swap(void **a, void **b)
{
	void	*tmp;

	if (a == NULL || b == NULL)
		return ;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_case_sensitive_strcmp(char *s1, char *s2)
{
	while (ft_tolower(*s1) == ft_tolower(*s2) && ft_tolower(*s1))
	{
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

static void	sort_matches(t_list **matches)
{
	t_list	*i;
	t_list	*j;

	if (matches == NULL || *matches == NULL)
		return ;
	i = *matches;
	while (i != NULL)
	{
		j = *matches;
		while (j->next != NULL)
		{
			if (ft_case_sensitive_strcmp(j->content, j->next->content) > 0)
			{
				ft_swap(&j->content, &j->next->content);
			}
			j = j->next;
		}
		i = i->next;
	}
}





/*
 * NOTE:
 * -> "*" by it self skip dotfiles
 */
t_cmd	*parsing(char *line, t_list *env_lst)
{
	t_list	*tokens;
	t_list	*matches;

	(void)env_lst;
	tokens = get_tokens(line);
	if (tokens == NULL)
		return (NULL);
	matches = expand_wildcard(((t_token *)tokens->content)->data);
	print_tokens(tokens);
	ft_lstclear(&tokens, free_token);
	for (t_list *tmp = matches; tmp != NULL; tmp = tmp->next)
	{
		printf("matched node: %10s\n", (char *)tmp->content);
	}
	ft_lstclear(&matches, free);
	ft_lstclear(&env_lst, free_env);
	exit(0);
	return ((t_cmd *)tokens);
}
