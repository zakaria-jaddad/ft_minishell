
#include "../../includes/parsing/parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SYNTAX_E "bash: syntax error near unexpected token `%s'\n"

bool	is_logical_op(t_token_type type)
{
	return (type == TOKEN_IF_AND || type == TOKEN_IF_OR);
}

bool	is_type_word(t_token_type type)
{
	return (type == TOKEN_WORD || type == TOKEN_DOUBLE_QUOTE_WORD
		|| type == TOKEN_SINGLE_QUOTE_WORD);
}

bool is_type_redirection(t_token_type type)
{
	return (type == TOKEN_IN_REDIR || type == TOKEN_OUT_REDIR
		|| type == TOKEN_APPEND_REDIR || type == TOKEN_HEREDOC);
}

bool	check_logical_operator(t_list *tokens)
{
	t_token	*tok;

	if (tokens == NULL)
		return (false);
	tok = tokens->content;
	if (peak_prev(tokens) != TOKEN_PAR_CLOSE
		&& is_type_word(peak_prev(tokens)) != true)
		return (ft_fprintf(STDERR_FILENO, SYNTAX_E, tok->data), false);
	if (peak_next(tokens) != TOKEN_PAR_OPEN
		&& is_type_word(peak_next(tokens)) != true)
		return (ft_fprintf(STDERR_FILENO, SYNTAX_E, tok->data), false);
	return (true);
}

#define PIPE_SE "bash: syntax error near unexpected token `|'\n"

bool check_pipe(t_list *tokens)
{
    if (tokens == NULL)
        return false;
    if (is_type_word(peak_prev(tokens)) == false && peak_prev(tokens) != TOKEN_PAR_CLOSE)
        return (ft_fprintf(STDERR_FILENO, PIPE_SE), false);
    if (is_type_word(peak_next(tokens)) == false
        && is_type_redirection(peak_next(tokens) == false)
        && peak_next(tokens) != TOKEN_PAR_OPEN)
        return (ft_fprintf(STDERR_FILENO, PIPE_SE), false);
    return true;
}

bool check_redir(t_list *tokens)
{
        if (tokens == NULL)
                return false;
        return true;

        // check tokens before redir
        // check tokens after redir
}

// ---- per
#define CLOSE_PER_SE "bash: syntax error near unexpected token `)'\n"
#define OPEN_PER_SE "bash: syntax error near unexpected token `('\n"

static bool	is_empty_subshell(t_list *tokens)
{
	t_token	*tok;

	if (tokens == NULL)
		return (true);
	while (tokens)
	{
		tok = tokens->content;
		if (tok->type != TOKEN_WHITE_SPACE)
			return (false);
		tokens = tokens->next;
	}
	return (true);
}
t_list	*get_subshell(t_list **tokens)
{
	t_list	*subshell;
	t_list	*token_node;
	t_token	*tok;
	int		depth;

	depth = 1;
	subshell = NULL;
	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	*tokens = (*tokens)->next;
	while (*tokens)
	{
		tok = (*tokens)->content;
		if (tok->type == TOKEN_PAR_OPEN)
			depth++;
		else if (tok->type == TOKEN_PAR_CLOSE)
			depth--;
		if (depth == 0)
			break ;
		token_node = create_token_node(tok->type, tok->data);
		if (token_node == NULL)
			return (ft_lstclear(&subshell, free_token), NULL);
		ft_lstadd_back(&subshell, token_node);
		*tokens = (*tokens)->next;
	}
	if (*tokens == NULL)
		return (ft_fprintf(STDERR_FILENO, OPEN_PER_SE), ft_lstclear(&subshell,
				free_token), NULL);
	if (is_empty_subshell(subshell) == true)
		return (ft_fprintf(STDERR_FILENO, CLOSE_PER_SE), ft_lstclear(&subshell,
				free_token), NULL);
	*tokens = (*tokens)->next;
	return (subshell);
}

bool check_per(t_list *tokens)
{
        if (tokens == NULL)
                return false;
        if (peak_prev(tokens) == TOKEN_PAR_CLOSE)
                return (ft_fprintf(STDERR_FILENO, OPEN_PER_SE), false);
        return true;
}

// ---- end per

bool	syntax_check(t_list *tokens)
{
	t_token	*tok;
	t_list	*subshell;

	if (tokens == NULL)
		return (false);
	while (tokens)
	{
		tok = tokens->content;
		if (tok->type == TOKEN_PAR_OPEN)
		{
                        if (check_per(tokens) == false)
                                return false;
			subshell = get_subshell(&tokens);
			if (subshell == NULL)
				return (false);
			if (syntax_check(subshell) == false)
				return (ft_lstclear(&subshell, free_token), false);
                        continue ;
		}
		if (is_logical_op(tok->type) == true)
		{
			if (check_logical_operator(tokens) == false)
				return (false);
		}
		else if (tok->type == TOKEN_PIPE)
		{
			if (check_pipe(tokens) == false)
				return (false);
		}
                else if (is_redirection(tok) == true)
                {
			if (check_redir(tokens) == false)
				return (false);
                }
		else if (tok->type == TOKEN_PAR_CLOSE)
			return (ft_fprintf(STDERR_FILENO, CLOSE_PER_SE), false);
                if (tokens == NULL)
                        break ;
		tokens = tokens->next;
	}
	return (true);
}
