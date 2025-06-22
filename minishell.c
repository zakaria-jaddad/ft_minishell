
#include "includes/minishell.h"
#include "includes/parsing/ast.h"
#include "includes/parsing/env.h"
#include "includes/parsing/tokenize.h"
#include "includes/parsing/wildcards.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void		expand_simple_cmd(char **command, char ***arguments,
				t_cmd_simple *cmd);
char		**list_tokens_to_double_pointer(t_list *list);
void		expand_simple_cmd(char **command, char ***arguments,
				t_cmd_simple *cmd);
t_list	*get_enhanced_tokens(t_list *tokens, char *delim);
void		expand_command(char **command, t_list *command_t, t_list *env);

t_list *get_word_start(t_list *tokens)
{
	if (tokens == NULL)
		return (NULL);
	while (tokens &&  is_word(tokens->content) == true)
	{
		if (tokens->prev == NULL)
			break ;
		tokens = tokens->prev;
	}
	return (tokens);
}

bool validate_word(t_list *tokens_word)
{
	t_token *token;

	while (tokens_word && tokens_word->content)
	{
		token = tokens_word->content;
		if (check_token_type(token, TOKEN_WORD) == true)
		{
			tokens_word = tokens_word->next;
			continue ;
		}
		if (ft_strcmp(token->data, "*") == 0)
			return false;
		tokens_word = tokens_word->next;
	}
	return true;
}

char *get_pre_expanded_file_name(t_list *tokens)
{
	t_token *token;
	char *pre_expansion_name = NULL;

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

void 	remove_word_from_tokens(t_list **tokens)
{
	t_list *word_start;
	t_list *node_to_del;

	if (tokens == NULL || *tokens == NULL)
		return ;
	word_start = *tokens;
	while (*tokens && !is_word((*tokens)->content))
	{
		node_to_del = *tokens;
		(*tokens) = (*tokens)->next;
		ft_lst_rm_one(node_to_del, free_token);
	}
}

t_list *create_tokenized_filenames(t_list *filename)
{
	t_list *token_node;
	t_list *tokenized_filenames;
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

/* void append_filenames(t_list **tokens, t_list *tokenized_filenames) */
/* { */
/* 	t_list *start; */
/* 	t_list *end; */
/* 	t_list *node_to_del; */
/**/
/* 	print_tokens_data(tokenized_filenames); */
/**/
/* 	if (tokenized_filenames == NULL || tokens == NULL || *tokens == NULL)	 */
/* 		return ; */
/* 	start = (*tokens)->prev; */
/* 	while (*tokens && is_word((*tokens)->content))  */
/* 		*tokens = (*tokens)->next; */
/* 	end = *tokens; */
/* 	while (*tokens && *tokens != end) */
/* 	{ */
/* 		node_to_del = *tokens; */
/* 		*tokens = (*tokens)->next; */
/* 		ft_lst_rm_one(node_to_del, free_token); */
/* 	} */
/* 	*tokens = start->next; */
/* 	start->next = NULL; */
/* 	if (start != NULL) */
/* 	{ */
/* 		ft_lstadd_back(&start, tokenized_filenames); */
/* 		ft_lstadd_back(&start, end); */
/* 		*tokens = ft_lstfirst(start); */
/* 		return ; */
/* 	} */
/* 	*tokens = tokenized_filenames; */
/* } */

void append_filenames(t_list **enhanced_tokens, t_list **tokens_word_start, t_list *tokenized_filenames)
{
	t_list *start = NULL;
	t_list *end = NULL;
	t_list *tmp;
	t_list *curr;

	if (!tokens_word_start || !*tokens_word_start || !tokenized_filenames)
		return;
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
	t_list *last = ft_lstlast(tokenized_filenames);
	last->next = end;
	if (end)
		end->prev = last;
	while ((*tokens_word_start)->prev)
		*tokens_word_start = (*tokens_word_start)->prev;
}

t_list	*expand_me(t_list *tokens, t_list *env)
{
	t_token	*current_token;
	t_list	*node_to_del;
	t_list	*enhanced_tokens_head;
	t_list *enhanced_tokens;
	char	*key;
	t_env	*var;

	enhanced_tokens = get_enhanced_tokens(tokens, "$*?");
	if (enhanced_tokens == NULL)
		return (NULL);
	enhanced_tokens_head = enhanced_tokens;

	print_tokens(enhanced_tokens);
	printf("\n");

	while (enhanced_tokens)
	{
		current_token = enhanced_tokens->content;
		if (ft_strchr(current_token->data, '$') == NULL)
		{
			enhanced_tokens = enhanced_tokens->next;
			continue ;
		}
		if (
			ft_strcmp(current_token->data, "$") == 0 	&&
			check_token_type(current_token, TOKEN_WORD) 	&&
			(peak_next(enhanced_tokens) == TOKEN_DOUBLE_QUOTE_WORD || peak_next(enhanced_tokens) == TOKEN_SINGLE_QUOTE_WORD))
		{
			node_to_del = enhanced_tokens;
			enhanced_tokens = enhanced_tokens->next;
			ft_lst_rm_one(node_to_del, free);
			enhanced_tokens_head = ft_lstfirst(enhanced_tokens);
			continue ;
		}
		// TODO: HANDLE * after $
		if (
			ft_strcmp(current_token->data, "$") == 0 									&&
			(check_token_type(current_token, TOKEN_WORD) || check_token_type(current_token, TOKEN_DOUBLE_QUOTE_WORD)) 	&& 
			peak_next(enhanced_tokens) == current_token->type)
		{
			node_to_del = enhanced_tokens;
			enhanced_tokens = enhanced_tokens->next;
			ft_lst_rm_one(node_to_del, free);
			enhanced_tokens_head = ft_lstfirst(enhanced_tokens);
			// expanstion
			current_token = enhanced_tokens->content;
			key = current_token->data;
			var = get_env(env, key);
			free(current_token->data);
			if (var == NULL)
				current_token->data = ft_strdup(key);
			else
				current_token->data = ft_strdup(var->value);
			continue ;
		}
		enhanced_tokens_head = ft_lstfirst(enhanced_tokens);
		enhanced_tokens = enhanced_tokens->next;
	}

	// Wildcard expanstion
	enhanced_tokens = enhanced_tokens_head;
	while (enhanced_tokens)
	{
		current_token = enhanced_tokens->content;
		if (check_token_type(current_token, TOKEN_WORD) == true &&
      			ft_strcmp(current_token->data, "*") != 0)
		{
			enhanced_tokens = enhanced_tokens->next;
			continue ;
		}
		if (check_token_type(current_token, TOKEN_DOUBLE_QUOTE_WORD) == true || check_token_type(current_token, TOKEN_SINGLE_QUOTE_WORD) == true)
		{
			enhanced_tokens = enhanced_tokens->next;
			continue ;
		}
		t_list *current_word = get_word_start(enhanced_tokens);
		if (current_word == NULL)
			break ;
		if (validate_word(current_word) == false)
		{
			enhanced_tokens = enhanced_tokens->next;
			continue ;
		}
		char *pre_expansion_name = get_pre_expanded_file_name(current_word);
		if (pre_expansion_name == NULL)
			return (ft_lstclear(&enhanced_tokens, free_token), NULL);
		t_list *filenames = expand_wildcard(pre_expansion_name);
		if (filenames == NULL)
			return (ft_lstclear(&enhanced_tokens, free_token), NULL);
		t_list *tokenized_filename = create_tokenized_filenames(filenames);
		append_filenames(&enhanced_tokens, &current_word, tokenized_filename);
		enhanced_tokens_head = ft_lstfirst(current_word);
		if (enhanced_tokens != NULL)
			enhanced_tokens = enhanced_tokens->next;
		else
			break ;
	}
	return (enhanced_tokens_head);
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

void	expand_command(char **command, t_list *command_t, t_list *env)
{
	t_list	*expanded_command;

	(void)command;
	expanded_command = expand_me(command_t, env);
	print_tokens(expanded_command);
	printf("\n");
	exit(0);
}

void	expand_command(char **command, t_list *command_t, t_list *env)
{
	t_list	*expanded_command;

	(void)command;
	expanded_command = expand_me(command_t, env);
	print_tokens(expanded_command);
	printf("\n");
	exit(0);
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

t_list	*get_enhanced_tokens(t_list *tokens, char *delim)
{
	t_list	*enhanced_tokens;
	t_list	*new_tokens;
	t_token	*current_token;
	t_list	*split_token_data;

	enhanced_tokens = NULL;
	while (tokens)
	{
		current_token = tokens->content;
		if (current_token->data != NULL && *current_token->data == 0)
			new_tokens = create_token_node(current_token->type, "");
		else
		{
			split_token_data = ft_split_pro(current_token->data, delim);
			if (split_token_data == NULL)
				break ;
			new_tokens = create_tokens(split_token_data, current_token->type);
		}
		if (new_tokens == NULL)
			ft_lstclear(&enhanced_tokens, free_token);
		ft_lstadd_back(&enhanced_tokens, new_tokens);
		tokens = tokens->next;
	}
	return (enhanced_tokens);
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
