#include "../includes/execution.h"

void handle_ctrC_fork(int sig) {
  (void)sig;
  exit(status_x(130, 1));
}
