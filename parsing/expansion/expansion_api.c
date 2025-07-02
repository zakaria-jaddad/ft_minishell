#include "../../includes/minishell.h"
#include "../../includes/parsing/expansion.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

static t_list	*expand_word(t_list *tokenized_word, t_list *env)
{
	t_list	*expanded_tokenized_word;
	t_list	*expansion_lst;

	if (tokenized_word == NULL || env == NULL)
		return (NULL);
	expanded_tokenized_word = expand(tokenized_word, env);
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

void	expand_filename(char **filename, t_list *tokenized_filename,
		t_list *env)
{
	t_list	*filename_lst;

	if (filename == NULL || tokenized_filename == NULL || env == NULL)
		return ;
	filename_lst = expand_word(tokenized_filename, env);
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

t_list	*expand_arguments(t_list *tokenized_arguments, t_list *env)
{
	t_list	*arguments_lst;
	t_list	*word;
	t_list	*expanded_argument;

	arguments_lst = NULL;
	while (tokenized_arguments)
	{
		word = get_tokenizd_word(&tokenized_arguments);
		if (word == NULL)
			return (ft_lstclear(&arguments_lst, free), NULL);
		expanded_argument = expand_word(word, env);
		ft_lstclear(&word, free_token);
		if (expanded_argument == NULL)
			return (ft_lstclear(&arguments_lst, free), NULL);
		ft_lstadd_back(&arguments_lst, expanded_argument);
		if (tokenized_arguments == NULL)
			break ;
		tokenized_arguments = tokenized_arguments->next;
	}
	return (arguments_lst);
}

void check_expansion(t_list *command_tokens, bool *split)
{
        t_token *tok;

        while (command_tokens)
        {
                tok = command_tokens->content;
                if (tok->type == TOKEN_DOUBLE_QUOTE_WORD || tok->type == TOKEN_SINGLE_QUOTE_WORD)
                {
                        *split = true;
                        return ;
                }
                command_tokens = command_tokens->next;
        } 
}

t_list *get_first_equal_node(t_list *tokens)
{
        if (tokens == NULL)
                return (NULL);
        while (tokens)
        {
                if (ft_strchr(tokens->content, '=') != NULL)
                        return tokens;
                tokens = tokens->next;
        }
        return (NULL);
}


char	*get_string_command(t_list *command_lst, t_list *tokenized_command, t_list **tokenized_arguments, bool* split)
{
	t_list	*command_tokens;
        t_list *tmp;
	char	*command;

        tmp = tokenized_command;
	if (tokenized_arguments == NULL || tokenized_command == NULL)
		return (NULL);
	if (command_lst == NULL)
	{
		command_tokens = get_tokenizd_word(tokenized_arguments);
		if (command_tokens == NULL)
			return (NULL);
		command = tokens_to_str(command_tokens);
                *split = true;
		ft_lstclear(&command_tokens, free_token);
		return (command);
	}
        command_tokens = get_tokenizd_word(&tmp);
        print_tokens(command_tokens);
        if (command_tokens == NULL)
                return (NULL);
        check_expansion(command_tokens, split);
	command = tokens_to_str(command_tokens);
        /* if(ft_strcmp(command, command_lst->content) != 0) */
        /*         *split = true; */
        ft_lstclear(&command_tokens, free_token);
	return (ft_strdup(command_lst->content));
}

bool should_split(t_list *tokens)
{
        t_token *tok;

        while (tokens)
        {
                tok = tokens->content;
                if (tok->type == TOKEN_DOUBLE_QUOTE_WORD || tok->type == TOKEN_SINGLE_QUOTE_WORD)
                        return (true);
                tokens = tokens->prev;
        }
        return (false);
}

void pre_expansion(t_list **tokens)
{
        t_list *enhance_tokens_list;
        t_list *arg;
        if (tokens == NULL || *tokens == NULL)
                return ;
        while (*tokens)
        {
                arg = get_tokenizd_word(tokens);
                if (arg == NULL)
                        return ;
                t_list *locate_first_equal_node = get_first_equal_node(arg);
                if (locate_first_equal_node == NULL)
                        continue;
                if (should_split(locate_first_equal_node) == false)
                {
                        while (arg)
                        {
                                t_token *token = arg->content;
                                if (arg == locate_first_equal_node)
                                {
                                        while (arg) 
                                        {
                                                t_list *token_node  = create_token_node(TOKEN_DOUBLE_QUOTE_WORD, token->data);
                                                ft_lstadd_back(&enhance_tokens_list, token_node);
                                                arg = arg->next;
                                        }               
                                        break ;
                                }
                                t_list *token_node  = create_token_node(token->type, token->data);
                                ft_lstadd_back(&enhance_tokens_list, token_node);
                                arg = arg->next;
                        }
                }
                else
                {
                        while (arg)
                        {
                                t_token *token = arg->content;
                                t_list *token_node  = create_token_node(token->type, token->data);
                                ft_lstadd_back(&enhance_tokens_list, token_node);
                                arg = arg->next;
                        }
                }
                if (*tokens == NULL)
                        break ;
                *tokens = (*tokens)->next;
        }
        exit(0);
        *tokens = enhance_tokens_list;
}

// export'' will split ✓ 
// $av export will split X $av is nothing
// export will not split unless change in charset found

t_list	*expand_all(t_list *command_lst, t_list *tokenized_command, t_list *tokenized_arguments, 
		t_list *env)
{
        bool split = false;
	char	*command;

        (void) env;
	command = get_string_command(command_lst, tokenized_command, &tokenized_arguments, &split);
        if (command == NULL)
                return (NULL);

        // 
        printf("this is the current command : %s, will split %s\n", command, split == true ? "true" : "false");
        if (ft_strcmp(command, "export") == 0 && split == false)
                pre_expansion(&tokenized_arguments);
        exit(0);
	for (t_list *tmp = command_lst; tmp != NULL; tmp = tmp->next)
	{
		printf("\"%s\" ", (char *)tmp->content);
		fflush(stdout);
	}
	printf("\n");
	exit(0);
	return (NULL);
}

// export $a=$b --> export a b c=c d e
