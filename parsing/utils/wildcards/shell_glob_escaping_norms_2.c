/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_glob_escaping_norms_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:02:08 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 16:02:53 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

void	*init_pattern_and_matches(char **pattern, t_list **matches,
		t_list *patterns, char *path, t_list **new_matches)
{
	if (patterns == NULL || path == NULL || new_matches == NULL)
		return (NULL);
	*new_matches = NULL;
	*pattern = patterns->content;
	if (*pattern == NULL)
		return (NULL);
	*matches = get_dir_content(path);
	if (*matches == NULL)
		return (NULL);
	return (NOTNULL);
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

void	*init_new_path_and_fi(char **new_path, char *path, t_file_info **fi,
		t_file_info *matches_content)
{
	if (new_path == NULL || fi == NULL || path == NULL
		|| matches_content == NULL)
		return (NULL);
	(void)!(*new_path = ft_strdup(path), *fi = matches_content);
	if (*new_path == NULL || *fi == NULL)
		return (NULL);
	return (NOTNULL);
}

bool	is_valid_glob(char *pattern, t_file_info *fi)
{
	if (pattern == NULL || fi == NULL)
		return (false);
	return (glob(pattern, fi->file_name) == true && (*fi->file_name == *pattern
			|| *fi->file_name != '.'));
}
