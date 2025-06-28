#include "../includes/execution.h"
#include <readline/readline.h>
#include <unistd.h>

char *get_address(void *var) {
  static char str[19];
  char *hex;
  unsigned long ptr;
  int i;

  hex = "0123456789ABCDEF";
  ptr = (unsigned long)var;
  str[0] = '0';
  str[1] = 'x';
  i = 17;
  while (i > 1) {
    str[i] = hex[ptr % 16];
    ptr /= 16;
    i--;
  }
  str[18] = '\0';
  return (ft_strdup(str));
}

int run_heredoc(char *dilimiter, int expand, t_list *env_list) {
  char *line;
  char *tmp;
  char *res;
  int fd[2];

  (void)env_list;
  (void)expand;
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
  line = get_address(dilimiter);
  fd[0] = open(line, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  fd[1] = open(line, O_RDONLY);
  unlink(line);
  free(line);
  if (fd[0] < 0 || fd[1] < 0)
    return (ft_fprintf(2, "error heredoc file\n"), 1);
  write(fd[0], res, ft_strlen(res));
  close(fd[0]);
  return (fd[1]);
}

int handle_heredoc(t_list *tokens, t_list *env_list) {
  t_token *token;
  int expand;
  char *str;

  if (!tokens)
    return (-1);
  expand = 1;
  str = tokens_to_str(tokens);
  while (tokens) {
    token = tokens->content;
    if (token->type == TOKEN_DOUBLE_QUOTE_WORD ||
        token->type == TOKEN_DOUBLE_QUOTE_WORD)
      expand = 0;
    tokens = tokens->next;
  }
  return (run_heredoc(str, expand, env_list));
}
