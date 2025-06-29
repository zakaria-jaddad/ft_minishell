#include "../includes/execution.h"

void	handle_ctrC_fork(int sig)
{
	(void)sig;
	exit(1);
}
