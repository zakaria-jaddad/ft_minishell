/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:00:05 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/18 21:58:56 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"




void skip_redirections(t_list **tokens)
{
        t_token *token;
        t_list *filename;

        if (!tokens || !*tokens)
                return;

        while (*tokens)
        {
                token = (*tokens)->content;
                if (token == NULL)
                        break ;
                if (is_redirection(token) == false)
                        break;

                *tokens = (*tokens)->next;
                skip_front_spaces(tokens); 

                // check filename
                filename  = get_filename(tokens);
                if (filename == NULL)
                        panic("syntax error: expected filename after redirection");
                ft_lstclear(&filename, free_token);

                if (*tokens == NULL)
                        return ;
                *tokens = (*tokens)->next;
                skip_front_spaces(tokens);
        }
}

void move_redirection_after(t_list *cmd_node, t_list **redir_node)
{
        if (cmd_node == NULL || redir_node == NULL || *redir_node == NULL)
                return ;
        cmd_node = dup_simple_tokens(cmd_node);
        if (cmd_node == NULL)
                return ;
        if ((*redir_node)->prev != NULL)
        {
                // NOTE: 7di Karek
                t_list *prev = (*redir_node)->prev;
                t_list *cmd_tail = ft_lstlast(cmd_node);

                prev->next = cmd_node;
                cmd_node->prev = prev;

                cmd_tail->next = *redir_node;
                (*redir_node)->prev = cmd_tail;

                return;
        }
        ft_lstadd_back(&cmd_node, (*redir_node));
        *redir_node = cmd_node;
}


void enhance_redirection(t_list **redir_tokens, t_list **tokens)
{
        t_list *cmd_node; // redirection command
        t_list *redir_start; // redirection start position 

        if (redir_tokens == NULL || *redir_tokens == NULL)
                return ;
        if (tokens == NULL || *tokens == NULL)
                return ;

        cmd_node = (*redir_tokens);
        redir_start = (*redir_tokens);
        skip_redirections(&cmd_node);

        if (cmd_node != NULL && is_word(cmd_node->content))
        {
                move_redirection_after(cmd_node, redir_tokens);
                (*tokens) = ft_lstfirst(redir_start);
                *redir_tokens = redir_start;
                return ;
        }
        (*redir_tokens) = cmd_node;
}

void pre_ast(t_list **tokens)
{
        t_list *current_token;

        if (tokens == NULL)
                return ;
        current_token = *tokens;
        while (current_token)
        {
                if (is_redirection(current_token->content)) 
                {
                        enhance_redirection(&current_token, tokens);
                        continue ;
                }
                current_token = current_token->next;
        }
}
