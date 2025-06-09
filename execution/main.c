
#include "../includes/execution.h"

t_tree *create_tree_node(char *command, t_token_type type) {
  t_tree *node = malloc(sizeof(t_tree));
  if (!node) {
    perror("malloc");
    return NULL;
  }
  node->command = command ? ft_strdup(command) : NULL;
  node->arguments = NULL;
  node->left = NULL;
  node->right = NULL;
  node->type = type;
  node->infile = NULL;
  return node;
}

t_tree *parse_line_to_tree(char *line) {
  char **tokens = ft_split(line, ' ');
  if (!tokens)
    return NULL;

  t_tree *root = create_tree_node(tokens[0], TOKEN_DOUBLE_QUOTE_WORD);
  if (!root) {
    // Free tokens if root allocation fails.
    int i = 0;
    while (tokens[i]) {
      free(tokens[i]);
      i++;
    }
    free(tokens);
    return NULL;
  }

  if (tokens[1] && !ft_strcmp(tokens[1], "||")) {
    root->type = TOKEN_IF_OR;
    root->left = create_tree_node(tokens[0], TOKEN_DOUBLE_QUOTE_WORD);
    root->right = create_tree_node(tokens[2], TOKEN_DOUBLE_QUOTE_WORD);
  } else if (tokens[1] && !ft_strcmp(tokens[1], "&&")) {
    root->type = TOKEN_IF_AND;
    root->left = create_tree_node(tokens[0], TOKEN_DOUBLE_QUOTE_WORD);
    root->right = create_tree_node(tokens[2], TOKEN_DOUBLE_QUOTE_WORD);
  } else if (tokens[1]) {
    // If there is a second token but it's not || or &&, treat it as an
    // argument. This simplifies the example; a more robust parser would handle
    // multiple arguments. Here we're just attaching the second token as an
    // argument to the root command.
    t_list *new_arg = malloc(sizeof(t_list));
    if (!new_arg) {
      perror("malloc");
      // Free allocated memory
      free(root->command);
      free(root);
      int i = 0;
      while (tokens[i]) {
        free(tokens[i]);
        i++;
      }
      free(tokens);
      return NULL;
    }
    new_arg->content = ft_strdup(tokens[1]);
    new_arg->next = NULL;
    root->arguments = new_arg;
  }

  // Free tokens array and its contents

  int i = 0;
  while (tokens[i]) {
    free(tokens[i]);
    i++;
  }
  free(tokens);

  return root;
}

int main(int ac, char **av, char **env) {
  char *line;
  t_tree *t;
  t_list *envs;

  (void)ac;
  (void)av;
  envs = envs_init(env);
  manage_pwd(getcwd(NULL, 0));
  if (!manage_pwd(NULL))
    manage_pwd(get_env(envs, "PWD")->value);

  while (1) {
    line = readline("lawkmu:$");
    if (!line)
      break;

    t = parse_line_to_tree(line);
    if (t) {
      execution(t, envs);
      // Basic free to prevent memory leaks
      if (t->command)
        free(t->command);
      if (t->arguments) {
        if (t->arguments->content)
          free(t->arguments->content);
        free(t->arguments);
      }
      if (t->left) {
        if (t->left->command)
          free(t->left->command);
        free(t->left);
      }
      if (t->right) {
        if (t->right->command)
          free(t->right->command);
        free(t->right);
      }
      free(t);
    }
    free(line);
  }
  return (0);
}
