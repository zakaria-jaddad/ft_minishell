/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:04:50 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 16:12:38 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing/expansion.h"

t_list	*get_dir_content(char *dirname)
{
	t_list			*files;
	struct dirent	*dir_info;
	DIR				*dir;
	t_list			*file_node;

	files = NULL;
	if (dirname == NULL)
		return (NULL);
	dir = opendir(dirname);
	if (dir == NULL)
		return (NULL);
	while (true)
	{
		dir_info = readdir(dir);
		if (dir_info == NULL)
			break ;
		file_node = creat_file_node(dir_info->d_type, dir_info->d_name);
		if (file_node == NULL)
			return (ft_lstclear(&files, free_file_info), NULL);
		ft_lstadd_back(&files, file_node);
	}
	closedir(dir);
	return (files);
}

char	*get_cwd_name(void)
{
	char	path[PATH_MAX];
	char	*new_path;

	if (getcwd(path, PATH_MAX) == NULL)
		return (NULL);
	new_path = ft_strdup(path);
	if (new_path == NULL)
		return (NULL);
	append_str(&new_path, "/");
	return (new_path);
}

char	*join_lst(t_list *lst)
{
	char	*str;

	str = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		append_str(&str, lst->content);
		if (str == NULL)
			return (NULL);
		lst = lst->next;
	}
	return (str);
}

/*
 * @brief Check wither the given str is valid absolute path
 */
bool	is_valid_absolute_path(char *str)
{
	if (str == NULL)
		return (false);
	if (*str != '/')
		return (false);
	return (ft_strchr(str, '/') != NULL);
}

/*
 * @brief returns absolute path of the given dir
 */
char	*get_dir_path(t_list *lst)
{
	char	*str;
	char	*dir_path;
	int		backslash_position;
	int		i;

	(void)!(str = NULL, dir_path = NULL, backslash_position = 0, i = 0);
	if (lst == NULL)
		return (NULL);
	str = lst->content;
	if (is_valid_absolute_path(str) == false)
	{
		dir_path = get_cwd_name();
		if (str[ft_strlen(str) - 1] == '/')
			return (append_str(&dir_path, "/"), append_str(&dir_path, str),
				dir_path);
		else
			return (dir_path);
	}
	while (str[i])
		if (str[i++] == '/')
			backslash_position = i;
	return (ft_substr(str, 0, backslash_position));
}
