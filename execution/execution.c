/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouait-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:56:52 by mouait-e          #+#    #+#             */
/*   Updated: 2025/05/29 10:40:16 by mouait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include <unistd.h>

int run_in_pipe(t_cmd *t, t_list *envs);
int run_redir(t_cmd *t, t_list *envs);

char *valid_command(char *cmd, char *path) {
  char *rv;
  char *tmp;
  char **paths;
  int i;

  i = 0;
  paths = ft_split(path, ':');
  while (paths[i]) {
    tmp = ft_strjoin(paths[i], "/");
    rv = ft_strjoin(tmp, cmd);
    free(tmp);
    if (!access(rv, X_OK)) {
      break;
    }
    free(rv);
    rv = NULL;
    i++;
  }
  free_double_pointer((void **)paths);
  if (rv)
    return (rv);
  return (ft_strdup(cmd));
}

int count_args(t_list *tokens) {
  int i;
  t_token *token;

  if (!tokens || !tokens->content)
    i = 0;
  else
    i = 1;
  while (tokens) {
    token = tokens->content;
    if (token->type == TOKEN_WHITE_SPACE)
      i++;
    tokens = tokens->next;
  }
  return (i);
}

// TODO: USE errno to get the err status and print its error :))
void display_execve_error(void) {
  ft_fprintf(2, "execve error: %s\n", strerror(status_x(errno, 1)));
}

char **arr_add_front(char **to_add, char **arr) {
  char **rv;
  int i;
  int j;

  if (!to_add)
    return (arr);
  if (!arr)
    return (to_add);
  i = 0;
  j = 0;
  while (arr[i])
    i++;
  while (to_add[j++])
    i++;
  rv = malloc(sizeof(char *) * (i + 1));
  if (!rv)
    return (NULL);
  i = -1;
  while (to_add[++i])
    rv[i] = ft_strdup(to_add[i]);
  j = -1;
  while (arr[++j])
    rv[i++] = ft_strdup(arr[j]);
  rv[i] = NULL;
  free_double_pointer((void **)arr);
  free_double_pointer((void **)to_add);
  return (rv);
}

int not_builtin(t_cmd_simple *tree, t_list *env_list) {
  pid_t pid;
  char **envs;
  char **args;
  char *path;
  char *cmd;

  if (get_env(env_list, "PATH") && get_env(env_list, "PATH")->value) {
    pid = fork();
    if (pid < 0)
      return (ft_fprintf(2, "fork failed\n"), 1);
    if (pid == 0) {
      if (signal(SIGINT, handle_ctrC_fork) == SIG_ERR)
        ft_fprintf(STDERR_FILENO, "signal: error handling ctr+c!!\n");
      envs = envs_list_to_double_pointer(env_list);
      if (!envs)
        return (0);
      args =
          list_to_double_pointer(expand_arguments(tree->arguments, env_list));
      args = arr_add_front(
          list_to_double_pointer(expand_command(tree->command, env_list)),
          args);
      if (!args)
        exit(1);
      cmd = ft_strdup(args[0]);
      path = valid_command((char *)cmd, get_env(env_list, "PATH")->value);
      if (execve(path, args, envs) < 0) {
        free(path);
        display_execve_error();
        exit(status_x(0, 0));
      }
      free(path);
      free_double_pointer((void **)args);
      free_double_pointer((void **)envs);
      exit(status_x(0, 0));
    } else {
      wait(NULL);
    }
  } else
    return (1);
  return (0);
}

int execution_simple_commad(t_cmd_simple *cmd, t_list *envs) {
  char **args;

  args = list_to_double_pointer(expand_arguments(cmd->arguments, envs));
  if (ft_strcmp(tokens_to_str(cmd->command), "cd") == 0)
    return (_cd_(envs, args));
  if (ft_strcmp(tokens_to_str(cmd->command), "export") == 0)
    return (_export_(envs, args));
  if (ft_strcmp(tokens_to_str(cmd->command), "env") == 0)
    return (_env_(envs));
  if (ft_strcmp(tokens_to_str(cmd->command), "echo") == 0)
    return (_echo_(args), 0);
  if (ft_strcmp(tokens_to_str(cmd->command), "pwd") == 0)
    return (_pwd_(manage_pwd(NULL)));
  if (ft_strcmp(tokens_to_str(cmd->command), "unset") == 0)
    return (_unset_(envs, args), 0);
  if (ft_strcmp(tokens_to_str(cmd->command), "exit") == 0) {
    _exit_(args);
  }
  return (free_double_pointer((void **)args), not_builtin(cmd, envs));
}

void setup_pwd(t_env *pwd) {
  char cwd[PATH_MAX];

  if (getcwd(cwd, PATH_MAX))
    manage_pwd(cwd);
  else if (pwd)
    manage_pwd(pwd->value);
}

int execution(t_cmd *tree, t_list *env_list) {
  if (!tree || !env_list)
    return (1);
  setup_pwd(get_env(env_list, "PWD"));
  if (tree->type == NODE_IF_AND) {
    execution(tree->left, env_list);
    return (execution(tree->right, env_list));
  } else if (tree->type == NODE_IF_OR) {
    if (execution(tree->left, env_list))
      return (execution(tree->right, env_list));
    return (0);
  } else if (tree->type == NODE_PIPE) {
    return (run_in_pipe(tree, env_list));
  } else if (tree->type == NODE_IN_REDIR) {
    return (run_redir(tree, env_list));
  } else if (tree->type == NODE_OUT_REDIR) {
    return (run_redir(tree, env_list));
  } else if (tree->type == NODE_APPEND_REDIR) {
    return (run_redir(tree, env_list));
  } else if (tree->type == NODE_HEREDOC) {
    return (run_heredoc(tree, env_list));
  }
  return (execution_simple_commad(tree->content, env_list));
}
