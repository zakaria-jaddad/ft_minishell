/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/27 19:22:50 by zajaddad         ###   ########.fr       */
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

void	skip_par(t_list **tokens)
{
	t_token	*token;

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
	t_token	*token;

	// NOTE: parenthesis are valid no need to check
	/* (void ) token; */
	/* (void ) tokens; */
	while (tokens && tokens->content)
	{
		token = tokens->content;
		if (token->type == TOKEN_PAR_OPEN)
			skip_par(&tokens);
		if (token->type == TOKEN_IF_AND)
			return (tokens);
		if (tokens == NULL)
			break ;
		tokens = tokens->next;
	}
	return (NULL);
}

bool	is_between_parenthesis(t_list *tokens)
{
	t_list	*first_token_node;
	t_list	*last_token_node;

	if (tokens == NULL)
		return (false);
	first_token_node = tokens;
	last_token_node = ft_lstlast(tokens);
	if (last_token_node == NULL)
		return (false);
	if (((t_token *)first_token_node->content)->type == TOKEN_PAR_OPEN
		&& ((t_token *)last_token_node->content)->type == TOKEN_PAR_CLOSE)
		return (true);
	return (false);
}

void remove_parenthesis(t_list **tokens)
{
	t_list	*tmp;

	if (tokens == NULL)	
		return ;

	tmp = (*tokens);
	(*tokens) = (*tokens)->next;
	ft_lstdelone(tmp, free_token);
	tmp = ft_lstlast((*tokens));
	if (tmp == NULL)
		return ; 
	if (tmp->prev != NULL)
		tmp->prev->next = NULL;
	ft_lstdelone(tmp, free);
}
void skip_spaces(t_list **tokens)
{
	t_token	*token;

	if (tokens == NULL)
		return ;
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->type != TOKEN_WHITE_SPACE)
			break ;
		(*tokens) = (*tokens)->next;
	}
}

t_list	*getcommand(t_list **tokens)
{
	t_list	*commands;
	t_list	*command_node;
	t_token	*token;

	if (tokens == NULL)
		return (NULL);
	commands = NULL;
	command_node = NULL;
	while ((*tokens))
	{
		token = (*tokens)->content;
		if (token->type != TOKEN_WORD && token->type != TOKEN_DOUBLE_QUOTE_WORD
			&& token->type != TOKEN_SINGLE_QUOTE_WORD)
			break ;
		command_node = create_token_node(token->type, token->data);
		if (command_node == NULL)
			return (ft_lstclear(&commands, free_token), NULL);
		ft_lstadd_back(&commands, command_node);
		(*tokens) = (*tokens)->next;
	}
	return commands;
}

t_list *getarguments(t_list **tokens)
{
	t_list *arguments;
	t_list *argument_node;
	t_token *token;

	if (tokens == NULL)
		return (NULL);
	arguments = NULL;
	token = NULL;
	argument_node = NULL;
	while ((*tokens))
	{
		token = (*tokens)->content;
		argument_node = create_token_node(token->type, token->data);
		if (argument_node == NULL)
			return (ft_lstclear(&arguments, free_token), NULL);
		ft_lstadd_back(&arguments, argument_node);
		(*tokens) = (*tokens)->next;
	}
	return arguments;
}

t_cmd	*parseexec(t_list *tokens)
{
	t_cmd			 *cmd;
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	skip_spaces(&tokens);
	cmd->command = getcommand(&tokens);
	skip_spaces(&tokens);
	cmd->arguments = getarguments(&tokens);
	if (cmd->command == NULL)
		return  (NULL);
	printf("command:");
	fflush(stdout);
	for (t_list *tmp = cmd->command; tmp != NULL; tmp = tmp->next)
	{
		printf("%s", ((t_token *)tmp->content)->data);
		fflush(stdout);

	}
	printf("\n");
	printf("arguments:");
	fflush(stdout);
	for (t_list *tmp = cmd->arguments; tmp != NULL; tmp = tmp->next)
	{
		printf("%s", ((t_token *)tmp->content)->data);
		fflush(stdout);

	}
	/* print_tokens(tokens); */
	cmd->left = NULL;
	cmd->right = NULL;
	return cmd;
}

t_cmd	*creat_ast(t_list *tokens)
{
	t_list	*root;
	t_cmd *hello;

	if (is_between_parenthesis(tokens) == true)
		remove_parenthesis(&tokens);
	root = get_root(tokens);
	// NOTE: simple command
	if (root == NULL)
		hello = parseexec(tokens);
	else
		(void)0x0;
	(void) hello;
	return ((t_cmd *)root);
}

t_cmd	*parsing(t_list *tokens)
{
	// TODO: NOT IMPLEMENTED
	if (tokens == NULL)
		return (NULL);
	// TODO:  Get the root of tokens
	if (is_valid_per(tokens) == false)
		return (panic("(): Syntax Error"), NULL);
	(void)creat_ast(tokens);
	return (NOTNULL);
}
void	remove_es(t_list **tokens)
{
	t_list	*th;
	t_list	*tt;
	t_token	*token;
	int		lst_size;

	if (tokens == NULL)
		return ;
	(th = *tokens, lst_size = ft_lstsize(*tokens));
	while (th)
	{
		token = th->content;
		if ((token->type == TOKEN_DOUBLE_QUOTE_WORD
				|| token->type == TOKEN_SINGLE_QUOTE_WORD)
			&& token->data != NULL && *token->data == 0)
		{
			(tt = th, th = th->next, ft_lst_rm_one(tt, free_token));
			lst_size--;
			continue ;
		}
		if (th == NULL)
			return ;
		th = th->next;
	}
	if (lst_size == 0)
		*tokens = NULL;
}

t_cmd	*parsecmd(char *line, t_list *env_lst)
{
	t_list	*tokens;
	t_cmd	*cmd;

	(void)env_lst;
	tokens = gettokens(line);
	if (tokens == NULL)
		return (NULL);
	remove_es(&tokens);
	/* printf("tokens = %p\n", tokens); */
	/* print_tokens(tokens); */
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
