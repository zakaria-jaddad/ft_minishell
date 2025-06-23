/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:45:16 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/23 20:14:21 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../../libft/libft.h"
# include "env.h"
# include "file_info.h"
# include "tokenize.h"
# include <stdbool.h>
# include <stdio.h>

# define special_expansion " .,+-!@#$%^&*()[]{};:'\"<>/?|~`= \t\n"

t_list	*expand_me(t_list *tokens, t_list *env);
t_list	*get_enhanced_tokens(t_list *tokens, char *delim);

// Dolarsign Expansion
t_list	*expand_dollar(t_list *tokens, t_list *env);
void	word_expansion(char **str, t_list *env);
void	digit_expansion(char **str);
bool	is_valid_dollar_with_qs_next(t_list *current_token_node);
bool	is_valid_dollar_with_valid_var(t_list *current_token_node);
bool	is_valid_dollar_with_dollar(t_list *current_token_node);

// Wildcard Expansion
t_list	*expand_wildcard(t_list *tokens);
t_list	*get_dir_content(char *dirname);
t_list	*sgen(char *p, t_list *pa, t_list *nm, t_list *m);
char	*join_lst(t_list *lst);
char	*get_cwd_name(void);
char	*get_dir_path(t_list *lst);
bool	is_valid_absolute_path(char *str);
bool	is_dir_with_trailing_slash(t_file_info *file_info, t_list *patterns);
bool	is_regfile_with_slash(t_file_info *file_info, t_list *patterns);
bool	is_valid_next_pattern(t_list *patterns);
bool	is_valid_glob(char *pattern, t_file_info *fi);
bool	glob(const char *pattern, const char *text);
void	check_glob(const char *pattern, const char *text);
void	remove_path(t_list *matches, char *pattern);
void	sort_matches(t_list **matches);
void	*init_pattern_and_matches(char **pattern, t_list **matches,
			t_list *patterns, char *path);
void	*init_new_path_and_fi(char **new_path, char *path, t_file_info **fi,
			t_file_info *matches_content);
void	*clear_new_matches_and_matches(t_list **new_matches, t_list **matches);
void	append_file_name_to_path(char **path, char *file_name);
void	*nmmt(t_list **matches_tmp, t_list **new_matches, t_list **matches);

#endif // !EXPANSION_H
