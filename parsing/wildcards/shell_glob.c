/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_glob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:57:21 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 22:31:41 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/parsing.h"

int	get_backslash_pos_before_wildcard(char *str)
{
	int	i;
	int	backslash_position;

	i = 0;
	backslash_position = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == '*')
			break ;
		if (str[i++] == '/')
			backslash_position = i;
	}
	return (backslash_position);
}

static t_list	*shell_glob(char *path, char *pattern)
{
	t_list	*new_matches;
	t_list	*matches;
	t_list	*split_pattern;
	t_list	*glob;

	(void)!(new_matches = matches = glob = NULL);
	if (path == NULL || pattern == NULL)
		return (NULL);
	split_pattern = ft_split_pro_max(pattern
			+ get_backslash_pos_before_wildcard(pattern), "/");
	if (split_pattern == NULL)
		return (NULL);
	glob = sgen(path, split_pattern, new_matches, matches);
	if (glob == NULL)
		return (ft_lstclear(&split_pattern, free), NULL);
	return (ft_lstclear(&split_pattern, free), glob);
}

static t_list	*get_valid_matches(char *str)
{
	t_list	*str_lst;
	char	*pattern;
	char	*dir_path;
	t_list	*matches;

	if (str == NULL)
		return (NULL);
	str_lst = ft_split_pro_max(str, "*");
	if (str_lst == NULL)
		return (NULL);
	pattern = join_lst(str_lst);
	if (pattern == NULL)
		return (ft_lstclear(&str_lst, free), NULL);
	dir_path = get_dir_path(str_lst);
	if (dir_path == NULL)
		return (ft_lstclear(&str_lst, free), free(pattern), pattern = NULL,
			NULL);
	ft_lstclear(&str_lst, free);
	matches = shell_glob(dir_path, pattern);
	if (matches == NULL)
		return (free(pattern), pattern = NULL, free(dir_path), dir_path = NULL,
			NULL);
	remove_path(matches, pattern);
	(void)(free(pattern), pattern = NULL, free(dir_path), dir_path = NULL);
	return (matches);
}

t_list	*expand_wildcard(char *str)
{
	t_list	*matches;

	matches = NULL;
	if (str == NULL)
		return (NULL);
	matches = get_valid_matches(str);
	if (matches == NULL)
		return (NULL);
	sort_matches(&matches);
	return (matches);
}
