
#include "includes/minishell.h"
#include "libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

int status_x(int value, int modify);
void handle_ctrC(int sig) {
  (void)sig;
  write(1, "\n", 1);
  status_x(1, 1);
  rl_replace_line("", 0);
  rl_on_new_line();
  rl_redisplay();
}

int main(int _, char **__, char **env) {
  char *line;
  t_cmd *cmd;
  t_list *env_lst;

  env_lst = envs_init(env, _, __);
  if (env_lst == NULL)
    return (EXIT_FAILURE);
  // Register signal handler for SIGINT (Ctrl+C)
  if (signal(SIGINT, handle_ctrC) == SIG_ERR) {
    ft_fprintf(STDERR_FILENO, "signal: error handling ctr+c!!\n");
    return (1);
  };
  while (true) {
    line = readline("Hello Shell >> ");
    if (line == NULL)
      break;
    if (*line)
      add_history(line);
    cmd = parse_cmd(line, env_lst);
    if (cmd == NULL)
      continue;
    print_cmd(cmd, 0);
    // printf("%s\n",
    // char *command;
    // char **arguments;
    // list_to_string(((t_cmd_simple *)cmd->content)->command));
    // print_tokens_data(((t_cmd_simple *)cmd->content)->command);
    // expand_simple_cmd(&command, &arguments,
    // (t_cmd_simple *)cmd->content);
    // printf("cmd: %s\n", command);
    // printf("args1: %s\n", arguments[0]);
    // printf("args2: %s\n", arguments[1]);
    status_x(execution(cmd, env_lst), 1);
    // printf("$?: %d\n", status_x(0, 0));
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
  int counter;

  counter = 0;
  if (tokens == NULL)
    return (0);
  while (tokens) {
    if (check_token_type(tokens->content, TOKEN_WHITE_SPACE) == true)
      counter++;
    tokens = tokens->next;
  }
  return (counter);
}

char **list_tokens_to_double_pointer(t_list *list) {
  t_token *token;
  int space_counter;
  char **double_pointer;
  int i;

  skip_front_spaces(&list);
  if (list == NULL)
    return (NULL);
  space_counter = count_spaces(list);
  double_pointer = ft_calloc(space_counter + 1, sizeof(char *));
  if (double_pointer == NULL)
    return (NULL);
  i = 0;
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
  return (double_pointer);
}
