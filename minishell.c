

#include "includes/minishell.h"

int	main(int argc, char **argv)
{
        (void) argc;
        (void) argv;
        char *line = NULL;
        while ((line = readline("Hello Sheel >> ")))
        {
                printf("%s\n", line);
                free(line);
        }
        return (EXIT_SUCCESS);
}
