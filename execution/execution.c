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

char **tokens_to_args(t_list *tokens) {
  t_token *token;
  char **rv;
  char *tmp;
  int i;

  rv = NULL;
  rv = ft_calloc(count_args(tokens) + 1, sizeof(char *));
  i = 0;
  while (tokens) {
    token = tokens->content;
    if (token->type == TOKEN_WHITE_SPACE)
      i++;
    else {
      tmp = ft_strjoin(rv[i], token->data);
      free(rv[i]);
      rv[i] = tmp;
    }
    tokens = tokens->next;
  }
  return (rv);
}

void handle_ctrC_fork(int sig) {
  (void)sig;
  exit(status_x(130, 1));
}

// TODO: USE errno to get the err status and print its error :))
void display_execve_error(void) {
  ft_fprintf(2, "execve error: %s\n", strerror(status_x(errno, 1)));
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
      expand_command(&cmd, tree->command, env_list);
      if (ft_strncmp(cmd, "", ft_strlen(cmd)) == 0) {
        args =
            list_to_double_pointer(expand_arguments(tree->arguments, env_list));
        if (!args || !args[0])
          exit(status_x(1, 1));
        cmd = args[0];
      } else {
        ft_lstadd_front(&(tree->arguments),
                        create_token_node(TOKEN_WHITE_SPACE, " "));
        ft_lstadd_front(&(tree->arguments), ft_lstnew(tree->command->content));
        args =
            list_to_double_pointer(expand_arguments(tree->arguments, env_list));
      }
      path = valid_command(cmd, get_env(env_list, "PATH")->value);
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
  }
  return (execution_simple_commad(tree->content, env_list));
}

int open_file(char *file, int flags) {
  int fd;

  fd = open(file, flags, 0644);
  if (fd == -1) {
    ft_fprintf(STDERR_FILENO, "minishell: %s: no such file or directory\n",
               file);
    return (-1);
  }
  return (fd);
}

int found_file(t_cmd *t, t_node_type flag, t_list *envs) {
  int fd;
  char *file;

  expand_filename(&file, ((t_cmd_redir *)t->content)->filename, envs);
  fd = -1;
  if (flag == NODE_OUT_REDIR) // >
    fd = open_file(file, O_RDONLY | O_WRONLY | O_CREAT);
  else if (flag == NODE_IN_REDIR) // <
    fd = open_file(file, O_RDONLY);
  if (fd == -1)
    return (-1);
  return (fd);
}

void get_last_redir_fd(t_cmd *t, int *out, int *in, t_list *envs) {
  int fd;

  fd = -1;
  if (!t)
    return;
  if (NODE_OUT_REDIR == t->type) // >
  {
    *out = found_file(t, t->type, envs);
    if (*out == -1)
      return;
  } else if (NODE_IN_REDIR == t->type) // <
  {
    *in = found_file(t, t->type, envs);
    if (*in == -1)
      return;
  }
  if (t->right)
    get_last_redir_fd(t->right, out, in, envs);
}

int run_redir(t_cmd *t, t_list *envs) {
  int status;
  int out_fd;
  int in_fd;
  pid_t pid;

  status = 0;
  in_fd = 0;
  out_fd = 0;
  get_last_redir_fd(t, &out_fd, &in_fd, envs);
  if (in_fd == -1 || out_fd == -1)
    return (status_x(1, 1));
  pid = fork();
  if (0 == pid) {
    if (signal(SIGINT, handle_ctrC_fork) == SIG_ERR)
      ft_fprintf(STDERR_FILENO, "signal: error handling ctr+c!!\n");
    if (in_fd)
      dup2(in_fd, STDIN_FILENO);
    if (out_fd)
      dup2(out_fd, STDOUT_FILENO);
    status = execution(t->left, envs);
    if (in_fd)
      close(in_fd);
    if (out_fd)
      close(out_fd);
    exit(status);
  } else if (pid > 0) {
    waitpid(pid, &status, 0);
    if (in_fd)
      close(in_fd);
    if (out_fd)
      close(out_fd);
  } else
    return (ft_fprintf(2, "fork error!\n"), 1);
  return (status_x(status, 0));
}

int run_in_pipe(t_cmd *t, t_list *envs) {
  pid_t pid_left;
  pid_t pid_right;
  int status;
  int fd[2];

  if (pipe(fd) < 0)
    return (ft_fprintf(2, "pipe: error!\n"), 1);
  status = 0;
  pid_left = fork();
  if (pid_left < 0)
    return (close(fd[0]), close(fd[1]), ft_fprintf(2, "fork: error!!\n"), 1);
  if (pid_left == 0) {
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    status = execution(t->left, envs);
    exit(status);
  }
  pid_right = fork();
  if (pid_right < 0)
    return (close(fd[0]), close(fd[1]), waitpid(pid_left, 0, 0),
            ft_fprintf(2, "fork: error!!\n"), 1);
  if (pid_right == 0) {
    if (signal(SIGINT, handle_ctrC_fork) == SIG_ERR)
      ft_fprintf(STDERR_FILENO, "signal: error handling ctr+c!!\n");
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    status = execution(t->right, envs);
    exit(status);
  }
  close(fd[0]);
  close(fd[1]);
  waitpid(pid_left, NULL, 0);
  waitpid(pid_right, NULL, 0);
  return (status_x(status, 0));
}
