/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/22 20:08:57 by zajaddad         ###   ########.fr       */
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

static void	append_file_name(t_list **matches, char *file_name, char *path)
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
static void	*init_pattern_and_matches(char **pattern, t_list **matches,
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

static void	*clear_new_matches_and_matches(t_list **new_matches,
		t_list **matches)
{
	if (new_matches == NULL || matches == NULL)
		return (NULL);
	ft_lstclear(new_matches, free);
	ft_lstclear(matches, free);
	*new_matches = NULL;
	*matches = NULL;
	return (NULL);
}

static void	*init_new_path_and_fi(char **new_path, char *path, t_file_info **fi,
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

static bool	is_valid_glob(char *pattern, t_file_info *fi)
{
	if (pattern == NULL || fi == NULL)
		return (false);
	return (glob(pattern, fi->file_name) == true && (*fi->file_name == *pattern
			|| *fi->file_name != '.'));
}
/*
 * @brief
 * @info
 *      fi: file information
 * @param
 * @param
 * @return List of matched files to the given pattern
 */
t_list	*shell_glob(char *path, t_list *patterns, t_list *new_matches,
		t_list *matches)
{
	char		*new_path;
	char		*pattern;
	t_file_info	*fi;
	t_list		*matches_tmp;

	if (!init_pattern_and_matches(&pattern, &matches, patterns, path,
			&new_matches))
		return (NULL);
	matches_tmp = matches;
	while (matches)
	{
		if (!init_new_path_and_fi(&new_path, path, &fi, matches->content))
			return (clear_new_matches_and_matches(&new_matches, &matches));
		if (is_valid_glob(pattern, fi))
		{
			if (is_dir_with_trailing_slash(fi, patterns))
				if (is_valid_next_pattern(patterns))
					(void)(append_file_name_to_path(&new_path, fi->file_name),
						ft_lstadd_back(&new_matches, shell_glob(new_path,
								patterns->next->next, new_matches, matches)));
				else
					append_file_name(&new_matches, fi->file_name, new_path);
			else if (!is_regfile_with_slash(fi, patterns))
				append_file_name(&new_matches, fi->file_name, new_path);
		}
		(void)!(free(new_path), new_path = NULL, matches = matches->next);
	}
	return (ft_lstclear(&matches_tmp, free_file_info), new_matches);
}

t_list	*shell_glob_escaping_norms(char *path, char *pattern)
{
	t_list	*new_matches;
	t_list	*matches;
	t_list	*split_pattern;
	t_list	*glob;

	new_matches = NULL;
	matches = NULL;
	glob = NULL;
	if (path == NULL || pattern == NULL)
		return (NULL);
	split_pattern = ft_split_pro_max(pattern
			+ get_backslash_pos_before_wildcard(pattern), "/");
	if (split_pattern == NULL)
		return (NULL);
	glob = shell_glob(path, split_pattern, new_matches, matches);
	if (glob == NULL)
		return (ft_lstclear(&split_pattern, free), NULL);
	return (ft_lstclear(&split_pattern, free), glob);
}

int	count_slashes(char *str)
{
	int	slashes_count;

	slashes_count = 0;
	if (str == NULL)
		return (0);
	while (*str)
		if (*str++ == '/')
			slashes_count++;
	return (slashes_count);
}

static void	append_slash_if_so(char **str, char *pattern)
{
	if (str == NULL || pattern == NULL)
		return ;
	if (pattern[ft_strlen(pattern) - 1] == '/')
		append_str(str, "/");
}

/*
 * emp: extract_matched_path
 * @param
 *      ps: number of slashes in the pattern
 *      rs: number of remaining slashes
 * */
char	*emp(char *path, char *pattern)
{
	char	*start;
	char	*current;
	int		ps;
	int		rs;

	if (!path || !pattern)
		return (NULL);
	(ps = count_slashes(pattern), rs = ps, start = path, current = (path
			+ ft_strlen(path) - 1));
	while (current >= path)
	{
		if (*current == '/')
		{
			if (rs == 0)
			{
				start = current + 1;
				break ;
			}
			rs--;
		}
		current--;
	}
	if (rs > 0)
		return (NULL);
	return (ft_strdup(start));
}

/*
 * @brief Remove absolute path prefix
 * @example
 *      absolute path:  /home/zajaddad/Projects/ft_minishell/parsing/utils/
 *      pattern      :  parsi*//*/
 *      return path  : parsing/utils/
 *  @var
 *      sl: list of split pattern
*/
void	remove_path(t_list *matches, char *pattern)
{
	t_list	*sl;
	char	*tmp;

	if (matches == NULL || pattern == NULL)
		return ;
	(sl = ft_split_pro_max(pattern, "/"));
	if (sl == NULL)
		return ;
	(void)(pattern = join_lst(sl), ft_lstclear(&sl, free));
	if (pattern == NULL)
		return ;
	while (matches)
	{
		append_slash_if_so((char **)&matches->content, pattern);
		if (is_valid_absolute_path(pattern) == false)
		{
			(tmp = matches->content, matches->content = emp(matches->content,
					pattern));
			tmp = (free(tmp), NULL);
			if (matches->content == NULL)
				break ;
		}
		matches = matches->next;
	}
	(void)(free(pattern), pattern = NULL);
}

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
	matches = shell_glob_escaping_norms(dir_path, pattern);
	if (matches == NULL)
		return (free(pattern), pattern = NULL, free(dir_path), dir_path = NULL,
			NULL);
	remove_path(matches, pattern);
	(void)(free(pattern), pattern = NULL, free(dir_path), dir_path = NULL,
		NULL);
	return (matches);
}

void	ft_swap(void **a, void **b)
{
	void	*tmp;

	if (a == NULL || b == NULL)
		return ;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_case_sensitive_strcmp(char *s1, char *s2)
{
	while (ft_tolower(*s1) == ft_tolower(*s2) && ft_tolower(*s1))
	{
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

static void	sort_matches(t_list **matches)
{
	t_list	*i;
	t_list	*j;

	if (matches == NULL || *matches == NULL)
		return ;
	i = *matches;
	while (i != NULL)
	{
		j = *matches;
		while (j->next != NULL)
		{
			if (ft_case_sensitive_strcmp(j->content, j->next->content) > 0)
			{
				ft_swap(&j->content, &j->next->content);
			}
			j = j->next;
		}
		i = i->next;
	}
}



t_list	*expand_wildcard(char *str)
{
	t_list	*matches;

	matches = NULL;
	if (str == NULL)
		return (NULL);
	matches = get_valid_matches(str);
	if (matches == NULL)
		return (NULL);
	sort_matches(&matches);
	return (matches);
}

/*
 * NOTE:
 * -> "*" by it self skip dotfiles
 */
t_cmd	*parsing(char *line, t_list *env_lst)
{
	t_list	*tokens;
	t_list	*matches;

	(void)env_lst;
	tokens = get_tokens(line);
	if (tokens == NULL)
		return (NULL);
	matches = expand_wildcard(((t_token *)tokens->content)->data);
	print_tokens(tokens);
	ft_lstclear(&tokens, free_token);
	for (t_list *tmp = matches; tmp != NULL; tmp = tmp->next)
	{
		printf("matched node: %10s\n", (char *)tmp->content);
	}
	ft_lstclear(&matches, free);
	ft_lstclear(&env_lst, free_env);
	exit(0);
	return ((t_cmd *)tokens);
}
