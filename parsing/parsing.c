/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/17 01:43:25 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <stdbool.h>
#include <stdio.h>

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

	printf("\n");
	print_depth(depth);
	// Print current node
	if (depth == 0) {
		printf("root   : ");
	} else {
		printf("╰───   : ");
	}
	printf("type: %s\n", get_token_type(root->type));
	print_depth(depth + 3);
	printf("command: ");
	fflush(stdout);
	print_tokens(root->command);
	printf("\n");

	print_depth(depth + 3);
	printf("arguments: ");
	fflush(stdout);
	print_tokens(root->arguments);
	printf("\n");
	if (root->filename != NULL)
	{
		print_depth(depth + 3);
		printf("filename: ");
		fflush(stdout);
		for (t_list *tmp = root->filename; tmp != NULL ;tmp = tmp->next)
		{
			printf("%s", ((t_token *)tmp->content)->data);
			fflush(stdout);
		}
		printf("\n");
	}
	printf("\n");

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
	cmd = parsing(tokens);
	if (cmd == NULL)
		printf("(null)");
	print_cmd(cmd, 0);

	/* expand_command_if_so(&command, &arguments, cmd, env_lst); */
	// use here 
	//
	/* exit(0); */
	(void)cmd;
	/* ft_lstclear(&tokens, free_token); */
	/* for (t_list *tmp = matches; tmp != NULL; tmp = tmp->next) */
	/* { */
	/* 	printf("matched node: %10s\n", (char *)tmp->content); */
	/* } */
	/* ft_lstclear(&matches, free); */
	/* ft_lstclear(&env_lst, free_env); */
	/* exit(0); */
	return ((t_cmd *)tokens);
}
