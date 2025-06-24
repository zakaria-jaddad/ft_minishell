/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_glob_escaping_norms_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:59:03 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 22:27:37 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing/expansion.h"

static void	flb(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	last = ft_lstlast(*lst);
	if (last == NULL)
		*lst = new;
	else
	{
		last->next = new;
		new->prev = last;
	}
}

void	escape_else_if(t_file_info *fi, t_list *pa, t_list **nm, char *new_path)
{
	if (is_dir_with_trailing_slash(fi, pa))
		return ;
	if (!is_regfile_with_slash(fi, pa))
		append_file_name(nm, fi->file_name, new_path);
}

void	escape_else(t_file_info *fi, t_list *pa, t_list **nm, char *new_path)
{
	if (is_valid_next_pattern(pa))
		return ;
	else
		append_file_name(nm, fi->file_name, new_path);
}

/*
 * @brief sgen: shell_glob_escaping_norms
 * @param:
 *      p       : path
 *      pa      : pattern
 *      nm      : new_matches
 *      m       : matches
 *      mt      : matches tmp
 */
t_list	*sgen(char *p, t_list *pa, t_list *nm, t_list *m)
{
	char		*new_path;
	char		*pattern;
	t_file_info	*fi;
	t_list		*mt;

	if (!init_pattern_and_matches(&pattern, &m, pa, p) || !nmmt(&mt, &nm, &m))
		return (NULL);
	while (m)
	{
		if (!init_new_path_and_fi(&new_path, p, &fi, m->content))
			return (clear_new_matches_and_matches(&nm, &m));
		if (is_valid_glob(pattern, fi))
		{
			if (is_dir_with_trailing_slash(fi, pa))
			{
				if (is_valid_next_pattern(pa))
					(void)(append_file_name_to_path(&new_path, fi->file_name),
						flb(&nm, sgen(new_path, pa->next->next, nm, m)));
				escape_else(fi, pa, &nm, new_path);
			}
			escape_else_if(fi, pa, &nm, new_path);
		}
		(void)!(free(new_path), new_path = NULL, m = m->next);
	}
	return (ft_lstclear(&mt, free_file_info), nm);
}
