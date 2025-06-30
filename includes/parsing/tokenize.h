/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 07:49:40 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/30 19:52:20 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "../../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_PAR_OPEN,     // (
	TOKEN_PAR_CLOSE,    // )
	TOKEN_PIPE,         // |
	TOKEN_IN_REDIR,     // <
	TOKEN_OUT_REDIR,    // >
	TOKEN_IF_AND,       // &&
	TOKEN_IF_OR,        // ||
	TOKEN_HEREDOC,      // <<
	TOKEN_APPEND_REDIR, // >>
	TOKEN_WHITE_SPACE,  // \t " "
	TOKEN_WORD,         //
	TOKEN_DOUBLE_QUOTE_WORD,
	TOKEN_SINGLE_QUOTE_WORD,
	TOKEN_COMMAND,
	INVALID_TOKEN
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*data;
}					t_token;

bool				check_equal_in_last_token(t_list *tokens);
bool				is_last_token_type_space(t_list *tokens);
bool				is_wrapped_by_single_paren_pair(t_list *tokens);
void				print_split(t_list *line_lst);
void				print_tokens(t_list *tokens);
void				free_token(void *token);
void				append_str(char **current_data, char *to_append);
void				remove_es(t_list **tokens);
void				remove_per(t_list **tokens);
void				skip_prev_spaces(t_list **tokens);
void				skip_front_spaces(t_list **tokens);
void				remove_back_spaces(t_list **tokens);
void				remove_front_spaces(t_list **tokens);
t_list				*split_line(char *line);
t_list				*create_token_node(t_token_type token_type,
						char *token_data);
t_list				*tokenize_quotes(char *quote_type, t_token_type token_type,
						t_list **line_lst);
t_list				*get_tokens(char *line);
t_list				*get_token_node(t_list *line_lst);
t_list				*append_tokens(t_list **tokens, t_token_type token_type,
						char *token_data);
t_list				*insert_tokens(t_list **tokens, t_token_type token_type,
						char *token_data);
t_list				*dup_and_remove_simple_tokens(t_list *to_start);
t_list				*dup_tokens(t_list *tokens_start, t_list *token_end,
						bool add_last);
t_token				*create_token(t_token_type token_type, char *token_data);
t_list				*get_filename(t_list **tokens);
char				*get_token_type(t_token_type token);
t_token_type		peak_next(t_list *tokens);
t_token_type		peak_prev(t_list *tokens);
char				*get_token_data(t_token *token);
t_list				*get_tokenizd_word(t_list **tokens);
char				*tokens_to_str(t_list *tokens);

static inline bool	is_redirection(t_token *token)
{
	if (token == NULL)
		return (false);
	return (token->type == TOKEN_IN_REDIR || token->type == TOKEN_OUT_REDIR
		|| token->type == TOKEN_APPEND_REDIR || token->type == TOKEN_HEREDOC);
}

static inline void	print_tokens_data(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL)
	{
		ft_fprintf(STDOUT_FILENO, "(null) ");
		return ;
	}
	ft_fprintf(STDOUT_FILENO, "\"");
	while (tokens)
	{
		token = (t_token *)tokens->content;
		ft_fprintf(STDOUT_FILENO, "%s", token->data);
		fflush(stdout);
		tokens = tokens->next;
	}
	ft_fprintf(STDOUT_FILENO, "\"");
	ft_fprintf(STDOUT_FILENO, "\n");
}

static inline bool	check_token_type(t_token *token, t_token_type token_type)
{
	if (token == NULL)
		return (false);
	return (token->type == token_type);
}

static inline bool	is_word(t_token *token)
{
	if (token == NULL)
		return (false);
	return (token->type == TOKEN_WORD || token->type == TOKEN_DOUBLE_QUOTE_WORD
		|| token->type == TOKEN_SINGLE_QUOTE_WORD);
}


static inline bool	is_token_special(t_token *token)
{
	if (token == NULL)
		return (false);
	return (!(is_word(token) || check_token_type(token, TOKEN_WHITE_SPACE)));
}


#endif // !TOKENIZE_H
