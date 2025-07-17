/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:10:01 by zajaddad          #+#    #+#             */
/*   Updated: 2025/07/17 05:45:36 by zajaddad         ###   ########.fr       */
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

# define SPECIAL_EXPANSION " .,+-!@#$%^&()[]{};:'\"<>/|~`= \t\n" // ?*

t_list	*expand(t_list *tokens, t_list *env);
t_list	*get_enhanced_tokens(t_list *tokens, char *delim);
t_list	*create_tokens(t_list *data_lst, t_token_type tokens_type);
bool	is_assignment_statement(t_list *tokens);
t_list	*create_enhanced_tokens(t_list *tokens, bool is_dq);
bool	check_cmdt(t_list *cmdt);
void	pre_expansion(t_list *command, t_list *cmdt, t_list **tokens);
t_list	*extract_words_list(t_list *tokens);
int		count_spaces(char *s);

// Dollarsign Expansion
void	expand_dollar(t_list **tokens, t_list *env);
void	word_expansion(char **str, t_list *env);
void	digit_expansion(char **str);
bool	is_valid_dollar_with_qs_next(t_list *current_token_node);
bool	is_valid_dollar_with_valid_var(t_list *current_token_node);
bool	is_valid_dollar_with_dollar(t_list *current_token_node);
void	split_enhanced_tokens(t_list **tokens);

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
bool	init_pattern_and_matches(char **pattern, t_list **matches,
			t_list *patterns, char *path);
bool	init_new_path_and_fi(char **new_path, char *path, t_file_info **fi,
			t_file_info *matches_content);
void	*clear_new_matches_and_matches(t_list **new_matches, t_list **matches);
void	append_file_name_to_path(char **path, char *file_name);
bool	nmmt(t_list **matches_tmp, t_list **new_matches, t_list **matches);
t_list	*get_word(t_list *tokens);
bool	is_valid_word(t_list *tokens_word);
bool	is_valid_wildcard(t_list *current_token_node);
bool	set_matches(t_list **matches, t_list *wordt);
t_list	*create_tokenized_matches(t_list *filename);

// Expansion API
t_list	*expand_word(t_list *wordt, t_list *env);
t_list	*expand_arguments(t_list *tokenized_arguments, t_list *env);
t_list	*expand_command(t_list *tokenized_command, t_list *env);
void	expand_filename(char **filename, t_list *tokenized_filename,
			t_list *env);
char	**expand_all(t_list *cmdt, t_list *argt, t_list *env);

int		ist(t_list **tokens, t_list **tokens_tmp, t_list *wordt);
bool	is_word_and_space_found(t_token *token);
void	del_token(t_list **tokens_tmp, t_list **tokens);

#endif // !EXPANSION_H
