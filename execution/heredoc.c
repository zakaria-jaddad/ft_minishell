#include "../includes/execution.h"
#include <readline/readline.h>
#include <unistd.h>

char *get_address(void *var) {
  char str[19];
  char *hex;
  unsigned long ptr;
  int i;

  hex = "0123456789ABCDEF";
  ptr = (unsigned long)var;
  str[0] = '.';
  str[1] = 'x';
  i = 17;
  while (i > 1) {
    str[i] = hex[ptr % 16];
    ptr /= 16;
    i--;
  }
  str[18] = '\0';
  return (ft_strjoin("/tmp/", str));
}

char *run_heredoc(char *dilimiter, int expand, t_list *env_list) {
  char *line;
  char *tmp;
  char *res;
  int fd;

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
  fd = open(line, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0 || fd < 0)
    return (free(line), ft_fprintf(2, "error heredoc file\n"), NULL);
  write(fd, res, ft_strlen(res));
  close(fd);
  return (line);
}

char *handle_heredoc(t_list *tokens, t_list *env_list) {
  t_token *token;
  int expand;
  char *str;

  if (!tokens)
    return (NULL);
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
