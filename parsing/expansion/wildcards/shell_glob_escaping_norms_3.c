/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_glob_escaping_norms_3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:00:16 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 22:27:48 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing/expansion.h"

void	*nmmt(t_list **matches_tmp, t_list **new_matches, t_list **matches)
{
	if (matches_tmp == NULL || new_matches == NULL)
		return (NULL);
	*matches_tmp = *matches;
	*new_matches = NULL;
	return (!NULL);
}

bool	is_dir_with_trailing_slash(t_file_info *file_info, t_list *patterns)
{
	if (file_info == NULL || patterns == NULL)
		return (false);
	return (file_info->file_type == DT_DIR && patterns->next != NULL
		&& ft_strcmp(patterns->next->content, "/") == 0);
}

bool	is_regfile_with_slash(t_file_info *file_info, t_list *patterns)
{
	return (file_info->file_type == DT_REG && patterns->next != NULL
		&& ft_strcmp(patterns->next->content, "/") == 0);
}

bool	is_valid_next_pattern(t_list *patterns)
{
	return (patterns->next->next != NULL
		&& patterns->next->next->content != NULL);
}
