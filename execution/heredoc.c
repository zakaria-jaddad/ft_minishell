#include "../includes/execution.h"
#include <readline/readline.h>

int run_heredoc(t_cmd *t, t_list *env_list) {
  char *line;
  char *dilimiter;

  dilimiter = ((t_token *)((t_cmd_redir *)t->content)->filename->content)->data;
  line = readline("");
  while (ft_strcmp(line, dilimiter) != 0) {
    line = readline(">");
  }
  printf("%s\n", line);
  return (0);
}
