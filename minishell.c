

#include "includes/minishell.h"

int	main(int argc, char **argv)
{
  (void) argc;
  (void) argv;
  ft_fprintf(STDOUT_FILENO, "Hello Shell\n");
	return (EXIT_SUCCESS);
}
