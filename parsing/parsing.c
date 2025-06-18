/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/18 23:51:22 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

bool is_valid_per(t_list *tokens)
{
        int depth;
        t_token *token;

        (void)!(token = NULL, depth = 0);
        while (tokens != NULL) {
                token = tokens->content;

                if (token->type == TOKEN_PAR_OPEN) {
                        depth++;
                }
                else if (token->type == TOKEN_PAR_CLOSE) {
                        depth--;
                        if (depth < 0) {
                                return (ft_fprintf(STDERR_FILENO, 
                                                   "bash: syntax error near unexpected token `%s\'\n", token->data
                                                   ), false);
                        }
                }
                tokens = tokens->next;
        }
        if (depth != 0)
                return (ft_fprintf(STDERR_FILENO, "bash: syntax error near unexpected token `(\'\n" 
                                   ), false);
        return (true);
}

t_cmd	*parsing(t_list **tokens)
{

        // TODO: ADD A SYNTAX CHECKER
        
        remove_front_spaces(tokens);
        remove_back_spaces(tokens);


        // NOTE: Debug print
        print_tokens_data(*tokens);
        return ((t_cmd*) tokens);
         /* return (ast(tokens)); */
}

bool syntax_check(t_list **tokens)
{
        if (tokens == NULL || *tokens == NULL)
                return (false);
	if (is_valid_per(*tokens) == false)
		return (false);
        return (true);

}

t_cmd	*parse_cmd(char *line, t_list *env_lst)
{
	t_list	*tokens;
	t_cmd	*cmd;

	(void)env_lst;
	tokens = get_tokens(line);
	if (tokens == NULL)
		return (NULL);

        // syntax_check() NOTE IMPLEMENTED
        if (syntax_check(&tokens) == false)
                return (ft_lstclear(&tokens, free_token), NULL);
        pre_ast(&tokens);
	cmd = parsing(&tokens);

	/* if (cmd == NULL) */
	/* 	printf("(null)"); */
	/* print_cmd(cmd, 0); */

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
	return ((t_cmd *)NULL);
}
