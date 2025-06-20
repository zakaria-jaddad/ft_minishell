

#include "includes/minishell.h"
#include "includes/parsing/tokenize.h"
#include "libft/libft.h"
#include <stdlib.h>

void expand_simple_cmd(char **command, char ***arguments, t_cmd_simple *cmd);
int main(int _, char **__, char **env) {
  char *line;
  t_cmd *cmd;
  t_list *env_lst;
  char *command;
  char **arguments;

  env_lst = envs_init(env, _, __);
  if (env_lst == NULL)
    return (EXIT_FAILURE);
  while (true) {
    line = readline("Hello Shell >> ");
    if (line == NULL)
      break;
    cmd = parse_cmd(line, env_lst);
    if (cmd == NULL)
      continue;
    // print_cmd(cmd, 0);
    // printf("%s\n", list_to_string(((t_cmd_simple *)cmd->content)->command));
    // print_tokens_data(((t_cmd_simple *)cmd->content)->command);
    // NODE_COMMAND
    //
    expand_simple_cmd(&command, &arguments, (t_cmd_simple *)cmd->content);
    printf("cmd: %s\n", command);
    printf("args1: %s\n", arguments[0]);
    printf("args2: %s\n", arguments[1]);

    // execution(cmd, env_lst);
  }
  free(line);
  return (EXIT_SUCCESS);
}

char **list_tokens_to_double_pointer(t_list *list);
void expand_simple_cmd(char **command, char ***arguments, t_cmd_simple *cmd) {
  char *comand;
  char **args;

  comand = ft_strdup(((t_token *)(cmd->command->content))->data);
  args = list_tokens_to_double_pointer(cmd->arguments);
  *command = comand;
  if (args)
    *arguments = args;
}

int count_spaces(t_list *tokens) {
  int counter = 0;
  if (tokens == NULL)
    return 0;
  while (tokens) {
    if (check_token_type(tokens->content, TOKEN_WHITE_SPACE) == true)
      counter++;
    tokens = tokens->next;
  }
  return counter;
}

char **list_tokens_to_double_pointer(t_list *list) {

  t_token *token;
  skip_front_spaces(&list);
  if (list == NULL)
    return (NULL);
  int space_counter = count_spaces(list);
  char **double_pointer = ft_calloc(space_counter + 1, sizeof(char *));
  if (double_pointer == NULL)
    return (NULL);
  int i = 0;
  while (i < space_counter + 1) {
    token = list->content;
    while (list != NULL && !check_token_type(token, TOKEN_WHITE_SPACE)) {
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
  return double_pointer;
}
