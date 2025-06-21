

#include "includes/minishell.h"
#include "includes/parsing/ast.h"
#include "includes/parsing/tokenize.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void		expand_simple_cmd(char **command, char ***arguments,
				t_cmd_simple *cmd);
char		**list_tokens_to_double_pointer(t_list *list);
void		expand_simple_cmd(char **command, char ***arguments,
				t_cmd_simple *cmd);

void	execution_mimic(t_cmd *cmd, t_list *env)
{
	char	*command;
	char	**arguments;

	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->type == NODE_COMMAND)
	{
		command = NULL;
		arguments = NULL;
		expand_simple_cmd(&command, &arguments, (t_cmd_simple *)cmd->content);
		printf("cmd: %s\n", command);
		printf("arguments : ");
		fflush(stdout);
		while (*arguments != NULL)
		{
			printf("%s, ", *arguments);
			arguments++;
			fflush(stdout);
		}
	}
}

bool	is_valid_varname(t_list *split_token_data)
{
	if (split_token_data == NULL)
		return (false);
	if (ft_strcmp(split_token_data->content, "$") == 0)
		return (false);
	return (true);
}

t_list	*create_tokens(t_list *data_lst, t_token_type tokens_type)
{
	t_list	*new_tokens;
	t_list	*token_node;

	new_tokens = NULL;
	if (data_lst == NULL)
		return (NULL);
	while (data_lst)
	{
		token_node = create_token_node(tokens_type, data_lst->content);
		if (token_node == NULL)
			return (ft_lstclear(&new_tokens, free_token), NULL);
		ft_lstadd_back(&new_tokens, token_node);
		data_lst = data_lst->next;
	}
	return (new_tokens);
}
t_list	*get_enhanced_command_t(t_list *command_t)
{
	t_list	*enhanced_command_t;
	t_list	*new_tokens;
	t_token	*current_token;
	t_list	*split_token_data;

	enhanced_command_t = NULL;
	while (command_t)
	{
		current_token = command_t->content;
		split_token_data = ft_split_pro(current_token->data, "$");
		if (split_token_data == NULL)
			break ;
		new_tokens = create_tokens(split_token_data, current_token->type);
		if (new_tokens == NULL)
			ft_lstclear(&enhanced_command_t, free_token);
		ft_lstadd_back(&enhanced_command_t, new_tokens);
		command_t = command_t->next;
	}
	return (enhanced_command_t);
}



void	expand_command(char **command, t_list *command_t)
{
	t_list	*enhanced_command_t;
	t_list	*enhanced_command_t_head;
	t_token	*current_token;
	t_list *node_to_del;

	(void)command;
	enhanced_command_t = get_enhanced_command_t(command_t);
	while (enhanced_command_t)
	{
		current_token = enhanced_command_t->content;
		if (ft_strcmp(current_token->data, "$") == 0 &&
			check_token_type(current_token, TOKEN_WORD)
				&& (peak_next(enhanced_command_t) == TOKEN_DOUBLE_QUOTE_WORD
				|| peak_next(enhanced_command_t) == TOKEN_SINGLE_QUOTE_WORD))
		{
			node_to_del = enhanced_command_t;
			enhanced_command_t = enhanced_command_t->next;
			ft_lst_rm_one(node_to_del, free);
		}
		if (enhanced_command_t == NULL)
			break ;
		enhanced_command_t_head = ft_lstfirst(enhanced_command_t);
		enhanced_command_t = enhanced_command_t->next;
	}
	print_tokens_data(enhanced_command_t_head);
	/* for (t_list *tmp = enhanced_command_t; tmp != NULL; tmp = tmp->next) */
	/* 	printf("%s", (char *) tmp->content); */
	/* printf("\n"); */
	exit(0);
}

void	expand_simple_cmd(char **command, char ***arguments, t_cmd_simple *cmd)
{
	t_list	*command_t;
	t_list	*arguments_t;

	if (cmd == NULL)
		return ;
	command_t = cmd->command;
	(void)command_t;
	if (command_t == NULL)
		return ;
	expand_command(command, command_t);
	arguments_t = cmd->arguments;
	(void)arguments;
	(void)arguments_t;
	return ;
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
		/* execution_mimic(cmd, env_lst); */
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
