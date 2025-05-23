/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_glob_escaping_norms_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:59:03 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 16:04:06 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static bool	is_dir_with_trailing_slash(t_file_info *file_info, t_list *patterns)
{
	if (file_info == NULL || patterns == NULL)
		return (false);
	return (file_info->file_type == DT_DIR && patterns->next != NULL
		&& ft_strcmp(patterns->next->content, "/") == 0);
}

static bool	is_regfile_with_slash(t_file_info *file_info, t_list *patterns)
{
	return (file_info->file_type == DT_REG && patterns->next != NULL
		&& ft_strcmp(patterns->next->content, "/") == 0);
}

static bool	is_valid_next_pattern(t_list *patterns)
{
	return (patterns->next->next != NULL
		&& patterns->next->next->content != NULL);
}

static void	append_file_name_to_path(char **path, char *file_name)
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

/*
 * @param:
 *      p       : path
 *      pa      : pattern
 *      nm      : new_matches
 *      m       : matches
 */
t_list	*shell_glob_escaping_norms(char *p, t_list *pa, t_list *nm, t_list *m)
{
	char		*new_path;
	char		*pattern;
	t_file_info	*fi;
	t_list		*matches_tmp;

	if (!init_pattern_and_matches(&pattern, &m, pa, p, &nm))
		return (NULL);
	matches_tmp = m;
	while (m)
	{
		if (!init_new_path_and_fi(&new_path, p, &fi, m->content))
			return (clear_new_matches_and_matches(&nm, &m));
		if (is_valid_glob(pattern, fi))
			if (is_dir_with_trailing_slash(fi, pa))
				if (is_valid_next_pattern(pa))
					(void)(append_file_name_to_path(&new_path, fi->file_name),
						ft_lstadd_back(&nm, shell_glob_escaping_norms(new_path,
								pa->next->next, nm, m)));
				else
					append_file_name(&nm, fi->file_name, new_path);
			else if (!is_regfile_with_slash(fi, pa))
				append_file_name(&nm, fi->file_name, new_path);
		(void)!(free(new_path), new_path = NULL, m = m->next);
	}
	return (ft_lstclear(&matches_tmp, free_file_info), nm);
}
