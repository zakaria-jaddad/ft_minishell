/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/05/29 20:55:28 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_valid_per(t_list *tokens) {
    int depth = 0;
    
    while (tokens != NULL) {
        t_token *token = tokens->content;
        
        if (token->type == TOKEN_PAR_OPEN) {
            depth++;
        }
        else if (token->type == TOKEN_PAR_CLOSE) {
            depth--;
            if (depth < 0) {
                return false;
            }
        }
        tokens = tokens->next;
    }
    
    return (depth == 0);
}

bool	is_between_per(t_list *tokens)
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

void remove_per(t_list **tokens)
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
void remove_front_spaces(t_list **tokens, void (*del)(void *))
{
    t_list  *to_delete;
    t_token *token;

    if (tokens == NULL || *tokens == NULL || del == NULL)
        return;

    while (*tokens)
    {
        token = (*tokens)->content;
        if (token->type != TOKEN_WHITE_SPACE)
            break;
        
        to_delete = *tokens;
        *tokens = (*tokens)->next;
	to_delete->prev = NULL;
	to_delete->next = NULL;
        ft_lstdelone(to_delete, del);
    }
}

void remove_back_spaces(t_list **tokens, void (*del)(void *))
{
	t_token	*token;
	t_list *last_token_node;
	t_list *to_delete;

	if (tokens == NULL)
		return ;
	last_token_node = ft_lstlast(*tokens);
	if (last_token_node == NULL)
		return ;
	while (last_token_node)
	{
		token = last_token_node->content;
		if (token->type != TOKEN_WHITE_SPACE)
			break ;
		to_delete = last_token_node;
		last_token_node = last_token_node->prev;
		if (last_token_node != NULL)
			last_token_node->next = NULL;
		to_delete->next = NULL;
		to_delete->prev = NULL;
		ft_lstdelone(to_delete, del);
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
	remove_front_spaces(&tokens, free_token);
	cmd->command = getcommand(&tokens);
	remove_back_spaces(&tokens, free_token);
	cmd->arguments = getarguments(&tokens);
	if (cmd->command == NULL)
		return  (NULL);
	cmd->left = NULL;
	cmd->right = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->type = TOKEN_COMMAND; 
	return cmd;
}
t_list *sublst(t_list *start, t_list *end, bool add_last)
{
	t_list *lst;
	t_token *token;
	t_list *token_node;

	if (start == NULL || end == NULL)	
		return NULL;
	lst = NULL;
	while (start && start != end)
	{
		token = start->content;
		token_node = create_token_node(token->type, token->data);
		if (token_node == NULL)
			return (ft_lstclear(&lst, free_token), NULL);
		ft_lstadd_back(&lst, token_node);
		start = start->next;
	}
	if (start != NULL && add_last == true)
	{
		token = start->content;
		token_node = create_token_node(token->type, token->data);
		if (token_node == NULL)
			return (ft_lstclear(&lst, free_token), NULL);
		ft_lstadd_back(&lst, token_node);
	}
	return lst;
}

t_cmd	*new_ast_node(void)
{
	t_cmd			 *cmd;
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->left = NULL;
	cmd->right = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->command = NULL;
	cmd->arguments = NULL;
	cmd->type = 222222;
	return cmd;
}

t_cmd	*ast(t_list *tokens)
{
	t_cmd	*root;
	t_list	*tokens_root;
	t_list *right;
	t_list *left;

	right = left = NULL;
	remove_front_spaces(&tokens, free_token);
	remove_back_spaces(&tokens, free_token);
	/* print_tokens(tokens); */

	if (is_between_per(tokens) == true)
		remove_per(&tokens); // FIX: "()" heap-use-after-free

	tokens_root = get_root(tokens);
	if (tokens_root == NULL)
		return parseexec(tokens);

	// not a simple command
	left = sublst(tokens, tokens_root, false);
	right = sublst(tokens_root->next, ft_lstlast(tokens_root), true);
	
	root = new_ast_node();
	if (root == NULL)
		return (NULL); // TODO: FREE MEMORY
	root->type = ((t_token *)tokens_root->content)->type;
	t_token *token = tokens_root->content;
	t_list *command_node = create_token_node(token->type, token->data);
	if (command_node == NULL)
		return (ft_lstclear(&root->command, free_token), NULL);
	ft_lstadd_back(&root->command, command_node);
	root->left = ast(left);
	root->right = ast(right);
	return (root);
}

t_cmd	*parsing(t_list *tokens)
{
	if (tokens == NULL)
		return (NULL);
	// TODO:  Get the root of tokens
	if (is_valid_per(tokens) == false)
		return (panic("(): Syntax Error\n"), NULL);
	return (ast(tokens));
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

void print_depth(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("    ");
}

void print_cmd(t_cmd *root, int depth) 
{
	if (root == NULL)
		return;

	print_depth(depth);
	// Print current node
	if (depth == 0) {
		printf("root : ");
	} else {
		printf("---> : ");
	}
	printf("command: ");
	fflush(stdout);
	print_tokens(root->command);

	printf("arguments: ");
	fflush(stdout);
	print_tokens(root->arguments);

	print_cmd(root->left, depth + 1);
	print_cmd(root->right, depth + 1);
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
	print_cmd(cmd, 0);
	exit(0);
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
