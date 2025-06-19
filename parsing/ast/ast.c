
#include "../../includes/parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

t_list	*get_command(t_list **tokens)
{
	t_list	*commands;
	t_list	*command_node;
	t_token	*token;

	if (tokens == NULL)
		return (NULL);
	commands = NULL;
	command_node = NULL;
	skip_front_spaces(tokens);
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

t_list *get_arguments(t_list **tokens)
{
	t_list *arguments;
	t_list *argument_node;
	t_token *token;

	if (tokens == NULL)
		return (NULL);
	arguments = NULL;
	token = NULL;
	argument_node = NULL;
	skip_front_spaces(tokens);
	while ((*tokens))
	{
		token = (*tokens)->content;
		if (token->type != TOKEN_WORD && token->type != TOKEN_DOUBLE_QUOTE_WORD
			&& token->type != TOKEN_SINGLE_QUOTE_WORD)
			break ;
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
	remove_front_spaces(&tokens);
	cmd->command = get_command(&tokens);
	remove_back_spaces(&tokens);
	cmd->arguments = get_arguments(&tokens);
	if (cmd->command == NULL)
		return  (NULL);
	cmd->left = NULL;
	cmd->right = NULL;
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

t_list *dup_tokens(t_list *tokens_start, t_list *token_end)
{
	t_list *new_tokens;
	t_list *token_node;
	t_token *token;

	new_tokens = NULL;
	token = NULL;
	while (tokens_start)
        {
		token = tokens_start->content;
		if (token == NULL)
			return (ft_lstclear(&new_tokens, free_token), NULL);
		token_node = create_token_node(token->type, token->data);
		if (token_node == NULL)
			return (ft_lstclear(&new_tokens, free_token), NULL);
		ft_lstadd_back(&new_tokens, token_node);
		tokens_start = tokens_start->next;
	}
	return new_tokens;
}

t_cmd	*new_ast_node(void)
{
	t_cmd			 *cmd;
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->left = NULL;
	cmd->right = NULL;
	cmd->command = NULL;
	cmd->arguments = NULL;
	cmd->type = 222222;
	return cmd;
}






t_cmd	*ast(t_list *tokens)
{
	t_cmd	*root;
	t_list	*tokens_root;
	/* t_token	*tokens_root_token; */
	t_list *right;
	t_list *left;


	if (tokens == NULL)
		return (NULL);

	right = left = NULL;
	remove_front_spaces(&tokens);
	remove_back_spaces(&tokens);
	/* print_tokens(tokens); */

	if (tokens == NULL)
		return NULL;

	/* if (is_between_per(tokens) == true) */
	/* 	remove_per(&tokens); */

	tokens_root = get_root(tokens);
	if (tokens_root == NULL)
		return parseexec(tokens);

	root = new_ast_node();
	if (root == NULL)
		return (NULL); // TODO: FREE MEMORY
	root->type = ((t_token *)tokens_root->content)->type;
	t_token *token = tokens_root->content;
	root->command = create_token_node(token->type, token->data);
	if (root->command == NULL)
		return (NULL); // TODO: FREE MEMORY


	// not a simple command
	left = sublst(tokens, tokens_root, false);
	/* right = sublst(tokens_root->next, ft_lstlast(tokens_root), true); */
	right = dup_tokens(tokens_root->next);



	root->left = ast(left);
	root->right = ast(right);
	return (root);
}
