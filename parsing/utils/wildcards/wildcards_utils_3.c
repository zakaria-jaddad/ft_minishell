/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:15:27 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 16:17:25 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

t_list	*get_valid_matches(char *str)
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
	(void)(free(pattern), pattern = NULL, free(dir_path), dir_path = NULL,
		NULL);
	return (matches);
}
