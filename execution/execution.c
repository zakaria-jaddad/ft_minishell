/* ************************************************************************** */
/*                                                                            */
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

int run_in_pipe(t_cmd *t, t_list *envs);
int run_redir(t_cmd *t, t_list *envs);

int not_builtin(t_cmd_simple *tree, t_list *env_list) {
  pid_t pid;
  char **envs;
  char **args;

  if (get_env(env_list, "PATH") && get_env(env_list, "PATH")->value) {
    pid = fork();
    if (pid < 0)
      return (ft_fprintf(2, "fork failed\n"), 1);
    if (pid == 0) {
      envs = envs_list_to_double_pointer(env_list);
      if (!envs)
        return (0);
      args = list_to_double_pointer(tree->arguments);
      if (execve(ft_strjoin("/bin/", list_to_string(tree->command)), args,
                 envs) < 0)
        return (ft_fprintf(2, "error: execve!!\n"), 1);
      free_double_pointer((void **)envs);
      exit(0);
    } else
      wait(NULL);
  } else
    return (1);
  return (0);
}

int execution_helper(t_cmd_simple *cmd, t_list *envs) {
  char **args;

  args = list_to_double_pointer(cmd->arguments);
  if (ft_strcmp(list_to_string(cmd->command), "cd") == 0)
    return (_cd_(envs, args));
  if (ft_strcmp(list_to_string(cmd->command), "export") == 0)
    return (_export_(envs, args));
  if (ft_strcmp(list_to_string(cmd->command), "env") == 0)
    return (_env_(envs));
  if (ft_strcmp(list_to_string(cmd->command), "echo") == 0)
    return (_echo_(expand(args, envs), 0));
  if (ft_strcmp(list_to_string(cmd->command), "pwd") == 0)
    return (_pwd_(manage_pwd(NULL)));
  if (ft_strcmp(list_to_string(cmd->command), "unset") == 0)
    return (_unset_(envs, args), 0);
  if (ft_strcmp(list_to_string(cmd->command), "exit") == 0) {
    _exit_(args);
  }
  return (not_builtin(cmd, envs));
}

int execution(t_cmd *tree, t_list *env_list) {
  if (!tree || !env_list)
    return (1);
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
  return (execution_helper(tree->content, env_list));
}

int open_file(char *file, int flags) {
  int fd;

  fd = open(file, flags);
  if (fd == -1) {
    ft_fprintf(STDERR_FILENO, "minishell: %s: no such file or directory\n",
               file);
    return (-1);
  }
  return (fd);
}

int found_file(t_cmd *t, t_node_type flag) {
  int fd;

  fd = -1;
  if (flag == NODE_OUT_REDIR)
    // TODO: change from the t->content to the file name after expanding
    fd = open_file(list_to_string(((t_cmd_redir *)t->content)->filename),
                   O_WRONLY | O_CREAT);
  else if (flag == NODE_IN_REDIR)
    fd = open_file(list_to_string(((t_cmd_redir *)t->content)->filename),
                   O_RDONLY);
  return (fd);
}

int get_last_redir_fd(t_cmd *t, t_node_type flag) {
  int fd;

  fd = -1;
  if (!t)
    return (fd);
  if (NODE_OUT_REDIR == t->type) // >
  {
    fd = get_last_redir_fd(t->right, t->type);
    if (fd == -1)
      fd = found_file(t->left, flag);
  } else if (NODE_IN_REDIR == t->type) // <
  {
    fd = get_last_redir_fd(t->right, t->type);
    if (fd == -1)
      fd = found_file(t->left, flag);
  } else
    fd = found_file(t, flag);
  return (fd);
}

int run_redir(t_cmd *t, t_list *envs) {
  int status;
  int fd;
  pid_t pid;

  status = 0;
  fd = get_last_redir_fd(t->right, t->type);
  pid = fork();
  if (0 == pid) {
    if (t->type == NODE_IN_REDIR)
      dup2(fd, STDIN_FILENO);
    else if (t->type == NODE_OUT_REDIR)
      dup2(fd, STDOUT_FILENO);
    status = execution(t->left, envs);
    close(fd);
    exit(status);
  } else if (pid > 0) {
    close(fd);
    waitpid(pid, &status, 0);
  } else
    return (ft_fprintf(2, "fork error!\n"), 1);
  return (status);
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
  return (status);
}
