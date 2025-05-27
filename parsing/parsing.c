/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/27 10:18:35 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <stdio.h>

// TODO: FIX SCUFFED LOGIC )( is valid 
bool	is_valid_per(t_list *tokens)
{
	int		par_counter;
	t_token	*token;

	par_counter = 0;
	if (tokens == NULL)
		return (false);
	while (tokens && tokens->content)
	{
		token = tokens->content;
		if (token->type == TOKEN_PAR_OPEN)
			par_counter++;
		if (token->type == TOKEN_PAR_CLOSE)
			par_counter--;
		tokens = tokens->next;
	}
	if (par_counter == 0)
		return (true);
	return (false);
}

void skip_par(t_list **tokens)
{
	t_token *token;
	if (tokens == NULL)
		return ;
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->type == TOKEN_PAR_CLOSE)
			break ;
		(*tokens) = (*tokens)->next;
	}
}
/*
 * @brief get root function get the roo token from the given tokens
 */
t_list	*get_root(t_list *tokens)
{
	// NOTE: parenthesis are valid no need to check 
	t_token	*token;
	/* (void ) token; */
	/* (void ) tokens; */

	while (tokens && tokens->content)
	{
		token = tokens->content;
		if (token->type == TOKEN_PAR_OPEN)
			skip_par(&tokens);
		if (token->type == TOKEN_IF_AND)
			return tokens;
		if (tokens == NULL)
			break ;
		tokens = tokens->next;
	}
	return (NULL);
}

bool is_between_parenthesis(t_list *tokens)
{
	t_list *first_token_node;
	t_list *last_token_node;

	if (tokens == NULL)
		return false;
	first_token_node = tokens;
	last_token_node = ft_lstlast(tokens);
	if (last_token_node == NULL)
		return false;
	if (((t_token *)first_token_node->content)->type == TOKEN_PAR_OPEN
		&& ((t_token *)last_token_node->content)->type == TOKEN_PAR_CLOSE)
		return true;
	return false;
}
t_cmd *create_ast_node(t_list *tokens)
{
	t_list *command;
	t_token *token;

	if (tokens == NULL)
		return (NULL);
	command = NULL;
	// SKIP WHITE SPACE TOKESN
	while (tokens)
	{
		token = tokens->content;
		if 	(token->type != TOKEN_WHITE_SPACE)
			break;
		tokens = tokens->next;
	}
	while (tokens)
	{
		token = tokens->content;
		if 	(token->type != TOKEN_WORD
				&& token->type != TOKEN_DOUBLE_QUOTE_WORD
				&& token->type != TOKEN_SINGLE_QUOTE_WORD)
			break;
		ft_lstadd_back(&command, ft_lstnew(ft_strdup(token->data)));
		tokens = tokens->next;
	}
	printf("command: ");
	fflush(stdout);
	for (t_list *tmp = command; tmp  != NULL; tmp = tmp->next)
	{
		printf("%s", (char *) tmp->content);
		fflush(stdout);
	}

	exit(0);
}
t_cmd	*creat_ast(t_list *tokens)
{
	t_list	*root;
	t_list *tmp;

	root = get_root(tokens);
	if (root == NULL)
	{
		if (is_between_parenthesis(tokens) == true)
		{
			tmp = tokens;
			tokens = tokens->next;
			// free first totken which is (
			ft_lstdelone(tmp, free_token);

			// free last token which is )
			tmp = ft_lstlast(tokens);
			if (tmp == NULL)
				return (NULL); // TODO: DO SOMETHING
			ft_lstdelone(tmp, free);
			print_tokens(tokens);
			exit(0);
		}
		// TODO: STORE SIMPLE COMMAND
		else
			(void) create_ast_node(tokens);
	}

	if (root != NULL)
		printf("current root: %s, %s\n", get_token_type(((t_token *)root->content)->type), (((t_token *)root->content)->data));
	else 
		printf("current root is (null)\n");
	return (t_cmd *) root;
}

t_cmd	*parsing(t_list *tokens)
{

	// TODO: NOT IMPLEMENTED
	if (tokens == NULL)
		return (NULL);
	// TODO:  Get the root of tokens
	if (is_valid_per(tokens) == false)
		return (panic("(): Syntax Error"), NULL);
	(void) create_ast_node(tokens);
	return (NOTNULL);
}

t_cmd	*parsecmd(char *line, t_list *env_lst)
{
	t_list	*tokens;
	t_cmd	*cmd;

	(void)env_lst;
	tokens = gettokens(line);
	if (tokens == NULL)
		return (NULL);
	/*  NOTE: print_tokens(tokens); */
	cmd = parsing(tokens);
	(void)cmd;
	/* ft_lstclear(&tokens, free_token); */
	/* for (t_list *tmp = matches; tmp != NULL; tmp = tmp->next) */
	/* { */
	/* 	printf("matched node: %10s\n", (char *)tmp->content); */
	/* } */
	/* ft_lstclear(&matches, free); */
	/* ft_lstclear(&env_lst, free_env); */
	exit(0);
	return ((t_cmd *)tokens);
}
