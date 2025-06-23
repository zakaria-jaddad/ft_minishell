/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_glob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:57:21 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/23 20:26:23 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing/expansion.h"

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

static t_list	*shell_glob(char *path, char *pattern)
{
	t_list	*new_matches;
	t_list	*matches;
	t_list	*split_pattern;
	t_list	*glob;

	(void)!(new_matches = matches = glob = NULL);
	if (path == NULL || pattern == NULL)
		return (NULL);
	split_pattern = ft_split_pro_max(pattern
			+ get_backslash_pos_before_wildcard(pattern), "/");
	if (split_pattern == NULL)
		return (NULL);
	glob = sgen(path, split_pattern, new_matches, matches);
	if (glob == NULL)
		return (ft_lstclear(&split_pattern, free), NULL);
	return (ft_lstclear(&split_pattern, free), glob);
}

static t_list	*get_valid_matches(char *str)
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
	(void)(free(pattern), pattern = NULL, free(dir_path), dir_path = NULL);
	return (matches);
}

char	*tokens_to_str(t_list *tokens)
{
	t_token	*token;
	char	*rv;
	char	*tmp;

	rv = NULL;
	while (tokens)
	{
		token = tokens->content;
		tmp = ft_strjoin(rv, token->data);
		if (tmp == NULL)
			return (free(rv), NULL);
		free(rv);
		rv = tmp;
		tokens = tokens->next;
	}
	return (rv);
}

t_list	*get_word(t_list *tokens)
{
	if (tokens == NULL)
		return (NULL);
	while (tokens && is_word(tokens->content) == true)
	{
		if (tokens->prev == NULL)
			break ;
		tokens = tokens->prev;
	}
	return (get_filename(&tokens));
}

bool	is_valid_word(t_list *tokens_word)
{
	t_token	*token;

	while (tokens_word && tokens_word->content)
	{
		token = tokens_word->content;
		if (check_token_type(token, TOKEN_WORD) == true)
		{
			tokens_word = tokens_word->next;
			continue ;
		}
		if (ft_strcmp(token->data, "*") == 0)
			return (false);
		tokens_word = tokens_word->next;
	}
	return (true);
}

bool is_valid_wildcard(t_list *current_token_node)
{
    t_token *current_token;

    if (current_token_node == NULL)
        return false;
    current_token = current_token_node->content;
    if (check_token_type(current_token, TOKEN_WORD) &&
        ft_strcmp(current_token->data, "*") == 0)
        return true;
    // If quoted, not valid wildcard
    if (check_token_type(current_token, TOKEN_DOUBLE_QUOTE_WORD) ||
        check_token_type(current_token, TOKEN_SINGLE_QUOTE_WORD))
        return false;
    return false;
}

void	*set_matches(t_list **matches, t_list *word)
{
	char	*unexpanded_name;

	if (matches == NULL || word == NULL)
		return (NULL);
	unexpanded_name = tokens_to_str(word);
	if (unexpanded_name == NULL)
		return (ft_lstclear(&word, free_token), NULL);
	*matches = get_valid_matches(unexpanded_name);
	if (*matches == NULL)
		return (ft_lstclear(&word, free_token), free(unexpanded_name), NULL);
	sort_matches(matches);
	return (NOTNULL);
}

t_list	*create_tokenized_matches(t_list *filename)
{
	t_list	*token_node;
	t_list	*tokenized_filenames;

	if (filename == NULL)
		return (NULL);
	tokenized_filenames = NULL;
	while (filename)
	{
		token_node = create_token_node(TOKEN_WORD, filename->content);
		if (token_node == NULL)
			return (ft_lstclear(&tokenized_filenames, free_token), NULL);
		ft_lstadd_back(&tokenized_filenames, token_node);
		if (append_tokens(&tokenized_filenames, TOKEN_WHITE_SPACE, " ") == NULL)
			return (ft_lstclear(&tokenized_filenames, free_token), NULL);
		filename = filename->next;
	}
	return (tokenized_filenames);
}

void	insert_matches(t_list **tokens, t_list *filenames)
{
	t_list	*tokenized_filenames;
	t_list	*tokens_head;
	t_list	*tmp;

	if (tokens == NULL || *tokens == NULL || filenames == NULL)
		return ;
	tokens_head = *tokens;
	tokenized_filenames = create_tokenized_matches(filenames);
	if (tokenized_filenames == NULL)
		return ;
	tmp = dup_and_remove_simple_tokens(*tokens);
}

t_list	*expand_wildcard(t_list *tokens)
{
	t_list	*matches;
	t_list	*word;

	matches = NULL;
	while (tokens)
	{
		if (is_valid_wildcard(tokens) == true)
		{
			word = get_word(tokens);
			if (is_valid_word(word) == true)
			{
				if (set_matches(&matches, word) == NULL)
					return (ft_lstclear(&word, free_token), NULL);
				ft_lstclear(&word, free_token);
				return (create_tokenized_matches(matches));
			}
			ft_lstclear(&word, free_token);
		}
		tokens = tokens->next;
	}
	return (sort_matches(&matches), matches);
}
