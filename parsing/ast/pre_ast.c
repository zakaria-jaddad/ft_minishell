/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:00:05 by zajaddad          #+#    #+#             */
/*   Updated: 2025/06/18 04:32:43 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include <stdbool.h>
#include <stdio.h>

t_token_type peak_next(t_list *tokens)
{
        t_token *token;

        if (tokens == NULL)
                return (INVALID_TOKEN);
        tokens = tokens->next;
        skip_front_spaces(&tokens);
        if (tokens == NULL)
                return (INVALID_TOKEN);
        token = tokens->content;
        if (token == NULL)
                return (INVALID_TOKEN);
        return (token->type);
}

t_token_type peak_prev(t_list *tokens)
{
        t_token *token;

        if (tokens == NULL)
                return (INVALID_TOKEN);
        tokens = tokens->prev;
        skip_prev_spaces(&tokens);
        if (tokens == NULL)
                return (INVALID_TOKEN);
        token = tokens->content;
        if (token == NULL)
                return (INVALID_TOKEN);
        return (token->type);
}


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

bool is_token_special(t_token *token)
{
        if (token == NULL)
                return false;
        return !(is_word(token) || check_token_type(token, TOKEN_WHITE_SPACE));
                
}

t_list *append_tokens(t_list **tokens, t_token_type token_type, char *token_data)
{
        t_list *token_node;

        if (token_data == NULL || tokens == NULL)
                return (NULL);
        token_node = create_token_node(token_type, token_data);
        if (token_node == NULL)
                return (NULL);
        ft_lstadd_back(tokens, token_node);
        return (token_node);
}

t_list *insert_tokens(t_list **tokens, t_token_type token_type, char *token_data)
{
        t_list *token_node;

        if (token_data == NULL || tokens == NULL)
                return (NULL);
        token_node = create_token_node(token_type, token_data);
        if (token_node == NULL)
                return (NULL);
        ft_lstadd_front(tokens, token_node);
        return (token_node);
}

/*
 * @brief Duplicate tokens Untile found Special Token
 * Special Token : && || | > < >> << 
 *
 * @var: 
 *      - dtn: dup_simple_tokens
 */
t_list *dup_simple_tokens(t_list *to_start)
{
        t_list *simple_tokens;
        t_list *dsn;
        t_list *node_to_del;
        t_token *token;

        if (to_start == NULL)
                return (NULL);
        (void)(simple_tokens = NULL, token = NULL, node_to_del = NULL);
        while (to_start)
        {
                token = to_start->content;
                if (is_token_special(token) == true)             
                        break;
                dsn = create_token_node(token->type, token->data);
                if (dsn == NULL)
                        return (ft_lstclear(&simple_tokens, free_token), NULL);
                ft_lstadd_back(&simple_tokens, dsn);
                if (append_tokens(&simple_tokens, TOKEN_WHITE_SPACE, " ") == NULL)
                        return (ft_lstclear(&simple_tokens, free_token), NULL);
                (void)(node_to_del = to_start, to_start = to_start->next);
                ft_lst_rm_one(node_to_del, free_token);
        }
        if (insert_tokens(&simple_tokens, TOKEN_WHITE_SPACE, " ") == NULL)
                return (ft_lstclear(&simple_tokens, free_token), NULL);
        return simple_tokens;
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


void enhance_naked_redirection(t_list **redir_tokens, t_list **tokens)
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
                        enhance_naked_redirection(&current_token, tokens);
                        continue ;
                }
                current_token = current_token->next;
        }
}
