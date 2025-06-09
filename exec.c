

#include "includes/execution.h"
#include "libft/libft.h"
#include <stdio.h>

t_tree	*parse_line_to_tree(char *line);
void	free_tree(t_tree *root);

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*env_lst;
	t_tree	*t;

	(void)!((void)argc, argv);
	env_lst = envs_init(env);
	manage_pwd(getcwd(NULL, 0));
	if (!manage_pwd(NULL))
		manage_pwd(get_env(env_lst, "PWD")->value);
	if (env_lst == NULL)
		return (EXIT_FAILURE);
	status_x(0, 1);
	while (true)
	{
		line = readline("Hello Shell >> ");
		if (line == NULL)
			break ;
		t = parse_line_to_tree(line);
		status_x(execution(t, env_lst), 1);
		free_tree(t);
	}
	free(line);
	return (EXIT_SUCCESS);
}

void	free_tree(t_tree *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	if (root->command)
		free(root->command);
	ft_lstclear(&root->arguments, free);
	ft_lstclear(&root->infile, free);
	free(root);
}

t_tree	*create_tree_node(char *command, t_token_type type)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
	{
		perror("malloc");
		return (NULL);
	}
	node->command = command ? ft_strdup(command) : NULL;
	node->arguments = NULL;
	node->left = NULL;
	node->right = NULL;
	node->type = type;
	node->infile = NULL;
	return (node);
}

t_tree	*parse_line_to_tree(char *line)
{
	char	**tokens;
	t_tree	*root;
	int		i;
	t_list	*new_arg;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (NULL);
	root = create_tree_node(tokens[0], TOKEN_DOUBLE_QUOTE_WORD);
	if (!root)
	{
		// Free tokens if root allocation fails.
		i = 0;
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
		return (NULL);
	}
	if (tokens[1] && !ft_strcmp(tokens[1], "||"))
	{
		root->type = TOKEN_IF_OR;
		root->left = create_tree_node(tokens[0], TOKEN_DOUBLE_QUOTE_WORD);
		root->right = create_tree_node(tokens[2], TOKEN_DOUBLE_QUOTE_WORD);
	}
	else if (tokens[1] && !ft_strcmp(tokens[1], "&&"))
	{
		root->type = TOKEN_IF_AND;
		root->left = create_tree_node(tokens[0], TOKEN_DOUBLE_QUOTE_WORD);
		root->right = create_tree_node(tokens[2], TOKEN_DOUBLE_QUOTE_WORD);
	}
	else if (tokens[1] && !ft_strcmp(tokens[1], "|"))
	{
		root->type = TOKEN_PIPE;
		root->left = create_tree_node(tokens[0], TOKEN_DOUBLE_QUOTE_WORD);
		root->right = create_tree_node(tokens[2], TOKEN_DOUBLE_QUOTE_WORD);
	}
	else if (tokens[1] && !ft_strcmp(tokens[1], "<"))
	{
		root->type = TOKEN_IN_REDIR;
		root->left = create_tree_node(tokens[0], TOKEN_DOUBLE_QUOTE_WORD);
		root->right = create_tree_node(tokens[2], TOKEN_DOUBLE_QUOTE_WORD);
	}
	else if (tokens[1] && !ft_strcmp(tokens[1], ">"))
	{
		root->type = TOKEN_OUT_REDIR;
		root->left = create_tree_node(tokens[0], TOKEN_DOUBLE_QUOTE_WORD);
		root->right = create_tree_node(tokens[2], TOKEN_DOUBLE_QUOTE_WORD);
	}
	else if (tokens[1])
	{
		// If there is a second token but it's not || or &&, treat it as an
		// argument. This simplifies the example; a more robust parser would handle
		// multiple arguments. Here we're just attaching the second token as an
		// argument to the root command.
		new_arg = malloc(sizeof(t_list));
		if (!new_arg)
		{
			perror("malloc");
			// Free allocated memory
			free(root->command);
			free(root);
			i = 0;
			while (tokens[i])
			{
				free(tokens[i]);
				i++;
			}
			free(tokens);
			return (NULL);
		}
		new_arg->content = ft_strdup(tokens[1]);
		new_arg->next = NULL;
		root->arguments = new_arg;
	}
	// Free tokens array and its contents
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (root);
}
