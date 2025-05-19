/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/19 16:43:37 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <dirent.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* DT_BLK      This is a block device. */
/* DT_CHR      This is a character device. */
/* DT_DIR      This is a directory. */
/* DT_FIFO     This is a named pipe (FIFO). */
/* DT_LNK      This is a symbolic link. */
/* DT_REG      This is a regular file. */
/* DT_SOCK     This is a UNIX domain socket. */
/* DT_UNKNOWN  The file type could not be determined. */

void	free_file_info(void *file_info)
{
	if (file_info == NULL)
		return ;
	((t_file_info *)file_info)->file_name = (free(((t_file_info *)file_info)->file_name),
			NULL);
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
		if (ft_strcmp(dir_info->d_name, ".") == 0 || ft_strcmp(dir_info->d_name,
				"..") == 0)
			continue ;
		file_node = creat_file_node(dir_info->d_type, dir_info->d_name);
		if (file_node == NULL)
			return (ft_lstclear(&files, free_file_info), NULL);
		ft_lstadd_back(&files, file_node);
	}
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

void	print_dir_content(t_list *dir_content)
{
	t_file_info	*file_info;

	if (dir_content == NULL)
		printf("(null)");
	while (dir_content)
	{
		file_info = (t_file_info *)dir_content->content;
		printf("file_name: \"%s\" %-30s\n", file_info->file_name,
			get_file_type(file_info->file_type));
		dir_content = dir_content->next;
	}
	printf("\n");
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

bool	glob(const char *pattern, const char *text)
{
	while (*pattern != 0 && *text != 0)
	{
		if (*pattern == '*')
		{
			if (glob(pattern + 1, text) == true)
				return (true);
			text += 1;
		}
		else if (*pattern == *text)
			(void)(pattern++, text++);
		else
			return (false);
	}
	if (*text == 0)
	{
		while (*pattern == '*')
			pattern += 1;
		return (*pattern == 0);
	}
	return (false);
}

void	check_glob(const char *pattern, const char *text)
{
	printf("%s <=> %s => %s \n", pattern, text, glob(pattern,
			text) == true ? "true" : "false");
}

// valid absolute paths always start with slash
bool	is_valid_absolute_path(char *str)
{
	if (str == NULL)
		return (false);
	if (*str != '/')
		return (false);
	return (ft_strchr(str, '/') != NULL);
}

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

int	get_backslash_pos(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i++] == '/')
			return (i);
	}
	return (0);
}

static void	append_file_name(t_list **matches, char *file_name)
{
	t_list	*node;

	if (file_name == NULL || matches == NULL)
		return ;
	node = ft_lstnew((void *)ft_strdup(file_name));
	if (node == NULL)
		return ;
	ft_lstadd_back(matches, node);
}

t_list	*shell_glob(char *path, t_list *patterns)
{
	t_list		*matches;
	t_list		*new_matches;
	t_file_info	*file_info;
	char		*pattern;
	char		*new_path;

	matches = NULL;
	new_matches = NULL;
	file_info = NULL;
	pattern = NULL;
	new_path = NULL;
	if (patterns == NULL || path == NULL)
		return (NULL);
	(void)!(pattern = patterns->content, matches = get_dir_content(path));
	if (pattern == NULL || matches == NULL)
		return (NULL);
	while (matches)
	{
		(void)!(new_path = ft_strdup(path), file_info = matches->content);
		if (file_info == NULL || new_path == NULL)
			return (ft_lstclear(&new_matches, free), NULL);
		if (glob(pattern, file_info->file_name) == true)
		{
			if (file_info->file_type == DT_DIR && patterns->next != NULL
				&& ft_strcmp(patterns->next->content, "/") == 0)
			{
				if (patterns->next->next != NULL
					&& patterns->next->next->content != NULL)
					(void)!(append_str(&file_info->file_name, "/"),
						append_str(&new_path, file_info->file_name),
						ft_lstadd_back(&new_matches, shell_glob(new_path,
								patterns->next->next)), 0);
				else
					append_file_name(&new_matches, file_info->file_name);
			}
			else if (!(file_info->file_type == DT_REG && patterns->next != NULL
					&& ft_strcmp(patterns->next->content, "/") == 0))
				append_file_name(&new_matches, file_info->file_name);
		}
		(void)!(free(new_path), new_path = NULL, matches = matches->next);
	}
	return (new_matches);
}

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
void	expand_wildcard(t_list **tokens)
{
	t_token	*token;
	t_list	*str_lst;
	char	*pattern;
	char	*dir_path;
	t_list	*match_node;

	if (tokens == NULL || *tokens == NULL)
		return ;
	while (*tokens)
	{
		token = (*tokens)->content;
		/* NOTE: When no match leave previous token content */
		if (token->type == TOKEN_WORD && ft_strchr(token->data, '*') != NULL)
		{
			str_lst = ft_split_pro_max(token->data, "*");
			if (str_lst == NULL)
				return ;
			pattern = join_lst(str_lst);
			if (pattern == NULL)
				return (ft_lstclear(&str_lst, free));
			dir_path = get_dir_path(str_lst);
			if (dir_path == NULL)
				return (ft_lstclear(&str_lst, free));
			match_node = shell_glob(dir_path, ft_split_pro_max(pattern
						+ get_backslash_pos_before_wildcard(pattern), "/"));
			if (match_node == NULL)
			{
				printf("HELLLLLLLLLLLO\n");
				return ;
			}
			for (t_list *tmp = match_node; tmp != NULL; tmp = tmp->next)
			{
				printf("match_node: %10s \n", (char *)tmp->content);
				fflush(stdout);
			}
			printf("\n");
			(void)match_node;
		}
		*tokens = (*tokens)->next;
	}
}

/*
 * NOTE:
 * -> "*" by it self skip dotfiles
 */
t_cmd	*parsing(char *line, t_list *env_lst)
{
	t_list	*tokens;

	(void)env_lst;
	tokens = get_tokens(line);
	print_tokens(tokens);
	if (tokens == NULL)
		return (NULL);
	expand_wildcard(&tokens);
	return ((t_cmd *)tokens);
}
