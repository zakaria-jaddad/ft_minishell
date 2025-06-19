
#include "../../includes/parsing/parsing.h"

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
                // FIX: an argument can be bunch of words separated by spaces
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
	t_list *right;
	t_list *left;

	if (tokens == NULL)
		return (NULL);

	right = left = NULL;
	remove_front_spaces(&tokens);
	remove_back_spaces(&tokens);
	if (tokens == NULL)
		return NULL;
	if (is_between_per(tokens) == true)
		remove_per(&tokens);

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
	left = dup_tokens(tokens, tokens_root, false);
	right = dup_tokens(tokens_root->next, ft_lstlast(tokens_root), true);



	root->left = ast(left);
	root->right = ast(right);
	return (root);
}
