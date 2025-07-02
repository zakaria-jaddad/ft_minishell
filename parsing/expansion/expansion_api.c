#include "../../includes/minishell.h"
#include "../../includes/parsing/expansion.h"

static int	count_spaces(char *s)
{
	int	spaces;

	spaces = 0;
	while (*s)
	{
		if (*s == ' ')
			spaces++;
		s++;
	}
	return (spaces);
}
static bool	check_spaces(char *str)
{
	return (count_spaces(str) == (int)ft_strlen(str));
}

static int	is_valid_word_token(int type)
{
	return (type == TOKEN_WORD || type == TOKEN_DOUBLE_QUOTE_WORD
		|| type == TOKEN_SINGLE_QUOTE_WORD);
}

t_list	*extract_words_list(t_list *tokens)
{
	t_list	*result;
	t_token	*tok;
	char	*dup;
	t_list	*new_node;
	t_list	*tokenized_word;

	result = NULL;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok && is_valid_word_token(tok->type) && tok->data
			&& check_spaces(tok->data) == false)
		{
			tokenized_word = get_filename(&tokens);
			if (tokenized_word == NULL)
				return (ft_lstclear(&result, free), NULL);
			dup = tokens_to_str(tokenized_word);
			if (dup == NULL)
				return (ft_lstclear(&tokenized_word, free_token),
					ft_lstclear(&result, free), NULL);
			new_node = ft_lstnew(dup);
			if (new_node == NULL)
				return (free(dup), ft_lstclear(&tokenized_word, free_token),
					ft_lstclear(&result, free), NULL);
			ft_lstadd_back(&result, new_node);
			continue ;
		}
		tokens = tokens->next;
	}
	return (result);
}

static t_list	*expand_word(t_list *wordt, t_list *env)
{
	t_list	*expanded_tokenized_word;
	t_list	*expansion_lst;

	if (wordt == NULL || env == NULL)
		return (NULL);
	expanded_tokenized_word = expand(wordt, env);
	if (expanded_tokenized_word == NULL)
		return (NULL);
	expansion_lst = extract_words_list(expanded_tokenized_word);
	return (expansion_lst);
}

t_list	*expand_command(t_list *tokenized_command, t_list *env)
{
	t_list	*expanded_word;

	expanded_word = expand_word(tokenized_command, env);
	if (tokenized_command == NULL || env == NULL)
		return (NULL);
	return (expanded_word);
}

void	expand_filename(char **filename, t_list *filenamet, t_list *env)
{
	t_list	*filename_lst;

	if (filename == NULL || filenamet == NULL || env == NULL)
		return ;
	filename_lst = expand_word(filenamet, env);
	if (filename_lst == NULL)
		return ;
	if (ft_lstsize(filename_lst) > 1)
	{
		ft_fprintf(STDERR_FILENO, "bash: *: ambiguous redirect\n");
		status_x(1, true);
		ft_lstclear(&filename_lst, free);
		return ;
	}
	*filename = ft_strdup(filename_lst->content);
	ft_lstclear(&filename_lst, free);
}

t_list	*expand_arguments(t_list *argt, t_list *env)
{
	t_list	*arguments_lst;
	t_list	*word;
	t_list	*expanded_argument;

	arguments_lst = NULL;
	while (argt)
	{
		word = get_tokenizd_word(&argt);
		if (word == NULL)
			return (ft_lstclear(&arguments_lst, free), NULL);
		expanded_argument = expand_word(word, env);
		ft_lstclear(&word, free_token);
		if (expanded_argument == NULL)
			return (ft_lstclear(&arguments_lst, free), NULL);
		ft_lstadd_back(&arguments_lst, expanded_argument);
		if (argt == NULL)
			break ;
		argt = argt->next;
	}
	return (arguments_lst);
}

bool	check_cmdt(t_list *cmdt)
{
	t_list	*wordt;
	t_list	*wordt_head;
	t_token	*tok;

	if (cmdt == NULL)
		return (false);
	wordt = get_tokenizd_word(&cmdt);
	if (wordt == NULL)
		return (false);
	wordt_head = wordt;
	while (wordt)
	{
		tok = wordt->content;
		if (tok->type == TOKEN_DOUBLE_QUOTE_WORD
			|| tok->type == TOKEN_SINGLE_QUOTE_WORD)
			return (ft_lstclear(&wordt_head, free_token), true);
		wordt = wordt->next;
	}
	ft_lstclear(&wordt_head, free_token);
	return (false);
}

t_list	*locate_eq(t_list *tokens)
{
	t_token	*tok;

	if (tokens == NULL)
		return (NULL);
	while (tokens)
	{
		tok = tokens->content;
		if (tok == NULL)
			return (NULL);
		if (ft_strchr(tok->data, '=') != NULL)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

bool	key_validation(t_list *tokens)
{
	t_token	*tok;

	if (tokens == NULL)
		return (false);
	while (tokens)
	{
		tok = tokens->content;
		if (tok->type != TOKEN_WORD)
			return (false);
		if (ft_strchr(tok->data, '$') != NULL)
			return (false);
		tokens = tokens->prev;
	}
	return (true);
}

bool	is_assignment_statement(t_list *tokens)
{
	t_list	*eq;
	t_list	*et;

	et = get_enhanced_tokens(tokens, "=");
	eq = locate_eq(et);
	if (eq == NULL)
		return (ft_lstclear(&et, free_token), false);
	if (key_validation(eq) == false)
		return (ft_lstclear(&et, free_token), false);
	return (ft_lstclear(&et, free_token), true);
}

t_list	*create_enhanced_tokens(t_list *tokens, bool is_dq)
{
	t_token	*tok;
	t_list	*new_token_node;
	t_list	*new_enhanced_tokens;

	if (tokens == NULL)
		return (NULL);
	new_enhanced_tokens = NULL;
	while (tokens)
	{
		tok = tokens->content;
		if (tok == NULL)
			return (ft_lstclear(&new_enhanced_tokens, free_token), NULL);
		if (is_dq == true)
			new_token_node = create_token_node(TOKEN_DOUBLE_QUOTE_WORD,
					tok->data);
		else
			new_token_node = create_token_node(tok->type, tok->data);
		if (new_token_node == NULL)
			return (ft_lstclear(&new_enhanced_tokens, free_token), NULL);
		ft_lstadd_back(&new_enhanced_tokens, new_token_node);
		tokens = tokens->next;
	}
	return (new_enhanced_tokens);
}

void	pre_expansion(t_list **tokens)
{
	t_list	*tmp;
	t_list	*new_tokens;
	t_list	*argt;
	t_list	*wordt;

	if (tokens == NULL || *tokens == NULL)
		return ;
	tmp = *tokens;
	new_tokens = NULL;
	wordt = NULL;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == TOKEN_WHITE_SPACE)
		{
			tmp = tmp->next;
			continue ;
		}
		wordt = get_tokenizd_word(&tmp);
		if (wordt == NULL)
			return (ft_lstclear(&new_tokens, free_token));
		if (is_assignment_statement(wordt) == true)
		{
			argt = create_enhanced_tokens(wordt, true);
			if (argt == NULL)
				return (ft_lstclear(&new_tokens, free_token),
					ft_lstclear(&wordt, free_token));
			ft_lstadd_back(&new_tokens, argt);
			if (append_tokens(&new_tokens, TOKEN_WHITE_SPACE, " ") == NULL)
				return (ft_lstclear(&new_tokens, free_token),
					ft_lstclear(&wordt, free_token), ft_lstclear(&argt,
						free_token));
			continue ;
		}
		argt = create_enhanced_tokens(wordt, false);
		if (argt == NULL)
			return (ft_lstclear(&new_tokens, free_token), ft_lstclear(&wordt,
					free_token));
		ft_lstadd_back(&new_tokens, argt);
		if (append_tokens(&new_tokens, TOKEN_WHITE_SPACE, " ") == NULL)
			return (ft_lstclear(&new_tokens, free_token), ft_lstclear(&wordt,
					free_token), ft_lstclear(&argt, free_token));
		ft_lstclear(&wordt, free_token);
		if (tmp == NULL)
			break ;
		tmp = tmp->next;
	}
	ft_lstclear(tokens, free_token);
	*tokens = new_tokens;
}

// TODO: FIX LEAKS
char	**expand_all(t_list *cmdt, t_list *argt, t_list *env)
{
	t_list	*cmd;
	t_list	*args_lst;
	t_list	*argt_dup;
	char	**cmds;
	char	**args;

	cmd = expand_command(cmdt, env);
	argt_dup = dup_tokens(argt, ft_lstlast(argt), true);
	if (argt_dup == NULL)
	{
		cmds = list_to_double_pointer(cmd);
		ft_lstclear(&cmd, free);
		return (cmds);
	}
	if (cmd != NULL && check_cmdt(argt_dup) == false)
		pre_expansion(&argt_dup);
	args_lst = expand_arguments(argt_dup, env);
	ft_lstclear(&argt_dup, free_token);
	cmds = list_to_double_pointer(cmd);
	ft_lstclear(&cmd, free);
	args = list_to_double_pointer(args_lst);
	ft_lstclear(&args_lst, free);
	return (arr_add_front(cmds, args));
}
