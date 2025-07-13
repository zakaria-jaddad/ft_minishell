/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:04:01 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/13 01:39:31 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing/tokenize.h"

static void	append_prev_word(t_list **lst, char *line, int i, int prev)
{
	char	*word;
	t_list	*node;

	if (i == prev)
		return ;
	word = ft_substr(line, 0, i - prev);
	if (word == NULL)
		return (ft_lstclear(lst, free));
	node = ft_lstnew(word);
	if (node == NULL)
	{
		ft_lstclear(lst, free);
		free(word);
		word = NULL;
		return ;
	}
	ft_lstadd_back(lst, node);
}

static void	append_special(t_list **lst, char *special, int *i, int *prev)
{
	t_list	*node;
	char	*special_dup;

	special_dup = ft_strdup(special);
	if (special_dup == NULL)
		return (ft_lstclear(lst, free));
	node = ft_lstnew(special_dup);
	if (node == NULL)
	{
		ft_lstclear(lst, free);
		free(special_dup);
		special_dup = NULL;
		return ;
	}
	ft_lstadd_back(lst, node);
	*i += ft_strlen(special_dup);
	*prev = *i;
}

static void	split_line_escaping_norms_2(t_list **lst, char *line, int *i,
		int *prev)
{
	if (line[*i] == '<')
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				"<", i, prev));
	else if (line[*i] == '|')
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				"|", i, prev));
	else if (line[*i] == '\"')
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				"\"", i, prev));
	else if (line[*i] == '\'')
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				"\'", i, prev));
	else if (line[*i] == ' ')
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				" ", i, prev));
	else if (line[*i] == '\t')
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				"\t", i, prev));
	else
		(*i)++;
}

static void	split_line_escaping_norms_1(t_list **lst, char *line, int *i,
		int *prev)
{
	if (ft_strnstr(&line[*i], "&&", ft_strlen("&&")) != NULL)
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				"&&", i, prev));
	else if (ft_strnstr(&line[*i], "||", ft_strlen("||")) != NULL)
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				"||", i, prev));
	else if (ft_strnstr(&line[*i], ">>", ft_strlen(">>")) != NULL)
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				">>", i, prev));
	else if (ft_strnstr(&line[*i], "<<", ft_strlen("<<")) != NULL)
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				"<<", i, prev));
	else if (line[*i] == '(')
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				"(", i, prev));
	else if (line[*i] == ')')
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				")", i, prev));
	else if (line[*i] == '>')
		(append_prev_word(lst, &line[*prev], *i, *prev), append_special(lst,
				">", i, prev));
	else
		split_line_escaping_norms_2(lst, line, i, prev);
}

t_list	*split_line(char *line)
{
	int		i;
	int		prev;
	t_list	*lst;

	i = 0;
	prev = 0;
	lst = NULL;
	while (line[i])
		split_line_escaping_norms_1(&lst, line, &i, &prev);
	if (line[i] == 0)
		(append_prev_word(&lst, &line[prev], i, prev));
	return (lst);
}
