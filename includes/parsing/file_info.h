/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 07:57:25 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/23 09:44:44 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_INFO_H
# define FILE_INFO_H

# include "../../libft/libft.h"
# include "tokenize.h"
# include <dirent.h>
# include <stdbool.h>

/*
 * @brief hold file information
 * s_file_info is used when expanding "*" wildcards
 * file_name is memory allocated
 */
typedef struct s_file_info
{
	unsigned char	file_type;
	char			*file_name;
}					t_file_info;

t_file_info			*creat_file_info(unsigned char file_type, char *file_name);
t_list				*creat_file_node(unsigned char file_type, char *file_name);
char				*get_file_type(unsigned char file_type);
void				print_dir_content(t_list *dir_content);
void				free_file_info(void *file_info);
void				append_file_name(t_list **matches, char *file_name,
						char *path);

#endif // !FILE_INFO_H
