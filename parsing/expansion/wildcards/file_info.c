/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:53:55 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/23 09:43:01 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing/file_info.h"

void	free_file_info(void *file_info)
{
	char	*file_name;

	if (file_info == NULL)
		return ;
	file_name = ((t_file_info *)file_info)->file_name;
	file_name = (free(file_name), NULL);
	free(file_info);
}

t_file_info	*creat_file_info(unsigned char file_type, char *file_name)
{
	t_file_info	*file_info;

	if (file_name == NULL)
		return (NULL);
	file_info = malloc(sizeof(t_file_info));
	if (file_info == NULL)
		return (NULL);
	ft_bzero(file_info, sizeof(t_file_info));
	file_info->file_type = file_type;
	file_info->file_name = ft_strdup(file_name);
	if (file_info->file_name == NULL)
		return (free(file_info), NULL);
	return (file_info);
}

t_list	*creat_file_node(unsigned char file_type, char *file_name)
{
	t_list		*node;
	t_file_info	*file_info;

	if (file_name == NULL)
		return (NULL);
	file_info = creat_file_info(file_type, file_name);
	if (file_info == NULL)
		return (NULL);
	node = ft_lstnew(file_info);
	if (node == NULL)
		return (free_file_info(file_info), file_info = NULL, NULL);
	return (node);
}

char	*get_file_type(unsigned char file_type)
{
	if (file_type == DT_DIR)
		return ("Directory");
	else if (file_type == DT_REG)
		return ("Regular File");
	else if (file_type == DT_UNKNOWN)
		return ("Unknown");
	else
		return ("Slak ou Safi");
}

void	append_file_name(t_list **matches, char *file_name, char *path)
{
	t_list	*node;
	char	*new_path;

	if (file_name == NULL || matches == NULL || path == NULL)
		return ;
	new_path = ft_strdup(path);
	if (new_path == NULL)
		return ;
	append_str(&new_path, file_name);
	node = ft_lstnew((void *)new_path);
	if (node == NULL)
		return ;
	ft_lstadd_back(matches, node);
}
