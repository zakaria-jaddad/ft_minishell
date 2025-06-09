#include "../../includes/execution.h"

int	main(int ac, char **av, char **env)
{
	t_tree	*t;
	t_list	*envs;

	(void)ac;
	t = malloc(sizeof(t_tree));
	t->left = malloc(sizeof(t_tree));
	t->right = malloc(sizeof(t_tree));
	t->command = NULL;
	t->arguments = NULL;
	t->infile = NULL;
	t->type = (t_token_type)TOKEN_IF_OR;
	t->left->command = ft_strdup("export");
	t->left->arguments = NULL;
	t->left->infile = NULL;
	t->left->type = TOKEN_DOUBLE_QUOTE_WORD;
	t->right->command = ft_strdup("env");
	t->right->arguments = NULL;
	t->right->infile = NULL;
	t->right->type = TOKEN_DOUBLE_QUOTE_WORD;
	envs = envs_init(env);
	execution(t, envs);
	free(t->left->command);
	free(t->right->command);
	free(t->left);
	free(t->right);
	free(t);
	return (0);
}
