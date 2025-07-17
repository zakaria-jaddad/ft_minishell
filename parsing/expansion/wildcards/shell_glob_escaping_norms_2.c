/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_glob_escaping_norms_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:02:08 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/17 06:01:55 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing/expansion.h"
#include <stdbool.h>

bool	init_pattern_and_matches(char **pattern, t_list **matches,
		t_list *patterns, char *path)
{
	if (patterns == NULL || path == NULL)
		return (false);
	*pattern = patterns->content;
	if (*pattern == NULL)
		return (false);
	*matches = get_dir_content(path);
	if (*matches == NULL)
		return (false);
	return (true);
}

void	*clear_new_matches_and_matches(t_list **new_matches, t_list **matches)
{
	if (new_matches == NULL || matches == NULL)
		return (NULL);
	ft_lstclear(new_matches, free);
	ft_lstclear(matches, free);
	*new_matches = NULL;
	*matches = NULL;
	return (NULL);
}

bool	init_new_path_and_fi(char **new_path, char *path, t_file_info **fi,
		t_file_info *matches_content)
{
	if (new_path == NULL || fi == NULL || path == NULL
		|| matches_content == NULL)
		return (false);
	(void)!(*new_path = ft_strdup(path), *fi = matches_content);
	if (*new_path == NULL || *fi == NULL)
		return (false);
	return (true);
}

bool	is_valid_glob(char *pattern, t_file_info *fi)
{
	if (pattern == NULL || fi == NULL)
		return (false);
	return (glob(pattern, fi->file_name) == true && (*fi->file_name == *pattern
			|| *fi->file_name != '.'));
}

void	append_file_name_to_path(char **path, char *file_name)
{
	char	*new_file_name;

	if (file_name == NULL)
		return ;
	new_file_name = ft_strdup(file_name);
	if (new_file_name == NULL)
		return ;
	append_str(&new_file_name, "/");
	append_str(path, new_file_name);
	free(new_file_name);
}
