/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:13:04 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/23 16:14:53 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static int	get_backslash_pos(char *str)
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

static int	count_slashes(char *str)
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
