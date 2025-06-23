
#include "includes/minishell.h"
#include "includes/parsing/ast.h"
#include "includes/parsing/env.h"
#include "includes/parsing/tokenize.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char		**list_tokens_to_double_pointer(t_list *list);
void		expand_simple_cmd(char **command, char ***arguments,
				t_cmd_simple *cmd);
void		expand_command(char **command, t_list *command_t, t_list *env);
void		expand_arguments(char ***arguments, t_list *argument_t,
				t_list *env);

t_list	*get_word_start(t_list *tokens)
{
	if (tokens == NULL)
		return (NULL);
	while (tokens && is_word(tokens->content) == true)
	{
		if (tokens->prev == NULL)
			break ;
		tokens = tokens->prev;
	}
	return (tokens);
}

bool	validate_word(t_list *tokens_word)
{
	t_token	*token;

	while (tokens_word && tokens_word->content)
	{
		token = tokens_word->content;
		if (check_token_type(token, TOKEN_WORD) == true)
		{
			tokens_word = tokens_word->next;
			continue ;
		}
		if (ft_strcmp(token->data, "*") == 0)
			return (false);
		tokens_word = tokens_word->next;
	}
	return (true);
}

char	*get_pre_expanded_file_name(t_list *tokens)
{
	t_token	*token;
	char	*pre_expansion_name;

	pre_expansion_name = NULL;
	while (tokens && tokens->content && is_word(tokens->content) == true)
	{
		token = tokens->content;
		append_str(&pre_expansion_name, token->data);
		if (pre_expansion_name == NULL)
			return (NULL);
		tokens = tokens->next;
	}
	return (pre_expansion_name);
}

void	remove_word_from_tokens(t_list **tokens)
{
	t_list	*node_to_del;

	if (tokens == NULL || *tokens == NULL)
		return ;
	while (*tokens && !is_word((*tokens)->content))
	{
		node_to_del = *tokens;
		(*tokens) = (*tokens)->next;
		ft_lst_rm_one(node_to_del, free_token);
	}
}

t_list	*create_tokenized_filenames(t_list *filename)
{
	t_list	*token_node;
	t_list	*tokenized_filenames;

	if (filename == NULL)
		return (NULL);
	tokenized_filenames = NULL;
	while (filename)
	{
		token_node = create_token_node(TOKEN_WORD, filename->content);
		if (token_node == NULL)
			return (ft_lstclear(&tokenized_filenames, free_token), NULL);
		ft_lstadd_back(&tokenized_filenames, token_node);
		if (append_tokens(&tokenized_filenames, TOKEN_WHITE_SPACE, " ") == NULL)
			return (ft_lstclear(&tokenized_filenames, free_token), NULL);
		filename = filename->next;
	}
	return (tokenized_filenames);
}

void	append_filenames(t_list **enhanced_tokens, t_list **tokens_word_start,
		t_list *tokenized_filenames)
{
	t_list	*start;
	t_list	*end;
	t_list	*tmp;
	t_list	*curr;
	t_list	*last;

	start = NULL;
	end = NULL;
	if (!tokens_word_start || !*tokens_word_start || !tokenized_filenames)
		return ;
	curr = *tokens_word_start;
	start = curr->prev;
	while (curr && is_word(curr->content))
		curr = curr->next;
	end = curr;
	curr = (start) ? start->next : *tokens_word_start;
	while (curr != end)
	{
		tmp = curr->next;
		ft_lst_rm_one(curr, free_token);
		curr = tmp;
	}
	if (start)
	{
		start->next = tokenized_filenames;
		tokenized_filenames->prev = start;
	}
	else
		*tokens_word_start = tokenized_filenames;
	*enhanced_tokens = ft_lstlast(tokenized_filenames);
	last = ft_lstlast(tokenized_filenames);
	last->next = end;
	if (end)
		end->prev = last;
	while ((*tokens_word_start)->prev)
		*tokens_word_start = (*tokens_word_start)->prev;
}



void	execution_mimic(t_cmd *cmd, t_list *env)
{
	char			*command;
	char			**arguments;
	t_cmd_simple	*simple_command;

	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->type == NODE_COMMAND)
	{
		simple_command = cmd->content;
		command = NULL;
		arguments = NULL;
		expand_command(&command, simple_command->command, env);
		expand_arguments(&arguments, simple_command->arguments, env);
                exit(0);
	}
}

void	expand_command(char **command, t_list *command_t, t_list *env)
{
	t_list	*expanded_command;

	(void)command;
	expanded_command = expand_me(command_t, env);
        printf("command: \n");
	print_tokens(expanded_command);
	printf("\n");
}

t_list	*get_tokenize_argument(t_list **tokenized_arguments)
{
	t_list	*tokenized_argument;
	t_list	*argument_node;
	t_token	*token;

	tokenized_argument = NULL;
	if (tokenized_arguments == NULL || *tokenized_arguments == NULL)
		return (NULL);
	while (tokenized_arguments && *tokenized_arguments && is_word((*tokenized_arguments)->content))
	{
		token = (*tokenized_arguments)->content;
		argument_node = create_token_node(token->type, token->data);
		if (argument_node == NULL)
			return (ft_lstclear(&tokenized_argument, free_token), NULL);
		ft_lstadd_back(&tokenized_argument, argument_node);
		(*tokenized_arguments) = (*tokenized_arguments)->next;
	}
	return (tokenized_argument);
}

void	expand_arguments(char ***arguments, t_list *tokenized_arguments, t_list *env)
{
	t_list	*expanded_arguments;
	t_list	*expanded_argument;
	t_list	*tokenize_argument;

	(void)arguments;
	expanded_arguments = NULL;
        print_tokens_data(tokenized_arguments);
	while (tokenized_arguments)
	{
		tokenize_argument = get_tokenize_argument(&tokenized_arguments);
		if (tokenize_argument == NULL)
			return (void)(ft_lstclear(&expanded_arguments, free_token), NULL);
		expanded_argument = expand_me(tokenize_argument, env);
		if (expanded_argument == NULL)
			return (void)(ft_lstclear(&tokenize_argument, free_token),
				ft_lstclear(&expanded_arguments, free_token), NULL);
		ft_lstadd_back(&expanded_arguments, expanded_argument);
                append_tokens(&expanded_argument, TOKEN_WHITE_SPACE, " ");
                skip_front_spaces(&tokenized_arguments);
                if (tokenized_arguments == NULL)
                        break ;
		tokenized_arguments = tokenized_arguments->next;
	}
        printf("arguments: \n");
        print_tokens(expanded_arguments);
        printf("\n");
}

int	main(int _, char **__, char **env)
{
	char	*line;
	t_cmd	*cmd;
	t_list	*env_lst;

	env_lst = envs_init(env, _, __);
	if (env_lst == NULL)
		return (EXIT_FAILURE);
	while (true)
	{
		line = readline("Hello Shell >> ");
		if (line == NULL)
			break ;
		cmd = parse_cmd(line, env_lst);
		print_cmd(cmd, 0);
		if (cmd == NULL)
			continue ;
		execution_mimic(cmd, env_lst);
		// execution(cmd, env_lst);
	}
	free(line);
	return (EXIT_SUCCESS);
}

static int	count_spaces(t_list *tokens)
{
	int	counter;

	counter = 0;
	if (tokens == NULL)
		return (0);
	while (tokens)
	{
		if (check_token_type(tokens->content, TOKEN_WHITE_SPACE) == true)
			counter++;
		tokens = tokens->next;
	}
	return (counter);
}

char	**list_tokens_to_double_pointer(t_list *list)
{
	t_token	*token;
	int		space_counter;
	char	**double_pointer;
	int		i;

	skip_front_spaces(&list);
	if (list == NULL)
		return (NULL);
	space_counter = count_spaces(list);
	double_pointer = ft_calloc(space_counter + 1, sizeof(char *));
	if (double_pointer == NULL)
		return (NULL);
	i = 0;
	while (i < space_counter + 1)
	{
		token = list->content;
		while (list != NULL && !check_token_type(token, TOKEN_WHITE_SPACE))
		{
			append_str(&double_pointer[i], token->data);
			if (double_pointer[i] == NULL)
				return (NULL); // TODO: MEMORY
			list = list->next;
			if (list)
				token = list->content;
		}
		i++;
		if (list)
			list = list->next;
	}
	return (double_pointer);
}
