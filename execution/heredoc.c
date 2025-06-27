#include "../includes/execution.h"
#include <readline/readline.h>
#include <unistd.h>

int run_heredoc(t_cmd *t, t_list *env_list) {
  char *line;
  char *tmp;
  char *res;
  char *dilimiter;
  int fd[2];

  (void)env_list;
  dilimiter = ((t_token *)((t_cmd_redir *)t->content)->filename->content)->data;
  line = readline(">");
  res = NULL;
  while (ft_strcmp(line, dilimiter) != 0) {
    tmp = ft_strjoin(res, line);
    free(res);
    res = tmp;
    tmp = ft_strjoin(res, "\n");
    free(res);
    res = tmp;
    free(line);
    line = readline(">");
  }
  free(line);
  if (!t->left)
    return (0);
  fd[0] = open("/tmp/test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  fd[1] = open("/tmp/test.txt", O_RDONLY);
  if (fd[0] < 0 || fd[1] < 0)
    return (ft_fprintf(2, "error heredoc file\n"), 1);
  write(fd[0], res, ft_strlen(res));
  close(fd[0]);
  fd[0] = fork();
  if (fd[0] == 0) {
    dup2(fd[1], STDIN_FILENO);
    execution(t->left, env_list);
    execution(t->right, env_list);
    close(fd[1]);
    exit(0);
  } else
    wait(NULL);
  close(fd[1]);
  return (0);
}
